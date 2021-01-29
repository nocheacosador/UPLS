#include "Winch.h"

#include <cmath>

Winch::Winch() : _en(false), _manual_duration(0.f), _extruder(EXTRUDER_DIR, EXTRUDER_PWM), 
	_target(0), _position(0), _status(Status::Unknown), _status_before_halt(Status::Unknown)
{ 
	memset(_prev_currents, 0, W_CURRENT_BUFFER_SIZE * sizeof(uint16_t));
}

void Winch::enable(bool enable) 
{
	if (enable && !_en)
	{
		_en = true;
		_motor.enable(true);
		_pos_ticker.attach(this, &Winch::m_motorPositionController, W_POSITION_PID_DT);
		_cur_ticker.attach(this, &Winch::m_motorCurrentSampler, 0.09f);
		_position = m_getPositionMeters();
		_target = _position;
		if (_position < 0.01f)
			_status = Status::Home;
		else
			_status = Status::Lowered;
	}
	else if (_en)
	{
		_pos_ticker.detach();
		_cur_ticker.detach();
		_motor.enable(false);
		memset(_prev_currents, 0, W_CURRENT_BUFFER_SIZE * sizeof(uint16_t));
		_value = 0.f;
		_current_sum = 0;
		_en = false;
		_status = Status::Unknown;
		_position = 0;
		_target = 0;
		_extruder.stop();
	}
}

void Winch::enableManual(bool en)
{
	if (en && _status != Status::Manual)
	{
		_status = Status::Manual;
		_timer.start();
		_manual_duration = 0.f;
		_value = 0.f;
		_target = 0;
	}
	else if (_status == Status::Manual)
	{
		_value = 0.f;
		_position = m_getPositionMeters();
		_target = _position;
		if (_position < 0.01f)
			_status = Status::Home;
		else
			_status = Status::Lowered;
		_timer.stop();
		_manual_duration = 0.f;
	}
}

void Winch::m_motorPositionController()
{
	_position = m_getPositionMeters();
	
	_motor.getSpeed();

	float pos_err = _target - _position;

	switch (_status)
	{
	case Status::GoingHome:
		if (getCurrent() > WINCH_HOME_SEARCHING_CUR_TRESH)
		{
			_value = 0.0f;
			_status = Status::Home;
			saveHome();
			_target = 0.f;
		}
		else if (_position > 1.0f)
			_value = WINCH_MAX_SPEED * -1.f;
		else
			_value = WINCH_HOME_SEARCHING_SPEED * -1.f;
		break;

	case Status::Home:
		//if (abs(_position) > 0.05f)
		//	_status = Status::GoingHome;
		_value = 0.f;
		break;

	case Status::Lowering:
		if (abs(pos_err) <= 0.01f)
		{	
			_value = 0.f;
			if (_motor.getSpeed() == 0.0f)
				_status = Status::Lowered;
		}
		else if (abs(pos_err) <= 0.1f)	
			_value = (pos_err) * 10.f * METERS_PER_SEC_TO_RPM(WINCH_LOWERING_GROUND_SPEED);
		else if (pos_err <= WINCH_SPEED_GROUND_DISTANCE)
			_value = METERS_PER_SEC_TO_RPM(WINCH_LOWERING_GROUND_SPEED);
		else if (_value < WINCH_MAX_SPEED)
			_value += WINCH_MAX_LOWERING_ACCELERATION * W_POSITION_PID_DT;
		else 
			_value = WINCH_MAX_SPEED;
		break;

	case Status::Lowered:
		if (abs(pos_err) > 0.05f)
			_status = Status::Lowering;
		break;

	case Status::Halted:
		_value = 0.f;
		break;

	case Status::Manual:
		if (_value != 0.f && _timer.read() >= _manual_duration)
		{
			_value = 0.f;
			_manual_duration = 0;
		}
		break;

	default:
		_value = 0.f;
		break;
	}

	_motor.speed(_value);
}

void Winch::m_motorCurrentSampler()
{
	_current_sum -= _prev_currents[_buf_index];
	_prev_currents[_buf_index] = uint16_t(_motor.getCurrent() * 1000.f);
	_current_sum += _prev_currents[_buf_index];
	_buf_index++;
	_buf_index %= W_CURRENT_BUFFER_SIZE;
}