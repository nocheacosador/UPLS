
#ifndef WINCH_H_
#define WINCH_H_

#include "../../include/global_macros.h"
#include "../MotorSpeedControl/MotorSpeedControl.h"
#include <Timer.h>
#include <Ticker.h>
#include "../Packet/packet.h"


#define W_MOTOR_SPEED_CONTROL
#define W_POSITION_PID_DT		0.2f
#define W_CURRENT_BUFFER_SIZE 	15
#define LOWEST_POINT			7.f	// meters

class Winch
{
public:
	typedef typename WinchInfo::Status Status;
	
	Winch();

	void enable(bool enable = true);
	
	bool isEnabled() { return _en; }

	void returnHome() 
	{ 
		if (_status != Status::Halted && _status != Status::Manual)
		{
			_status = Status::GoingHome;
			_target = 0.f;
			_value = 0.0f;
		}
	}
	void lower(float value = LOWEST_POINT)
	{
		if (_status != Status::Halted && _status != Status::Manual)
		{
			_status = Status::Lowering;
			_target = value;
			_value = 0.0f;
		}
	}	

	float getPosition() { return _position; }
	
	uint16_t getCurrent() { return _current_sum / W_CURRENT_BUFFER_SIZE; }

	float getTarget() { return _target; }

	Status getStatus() { return _status; }

	void saveHome() 
	{
		_position = m_getPositionMeters();
		_motor.encoder().reset();
		_target -= _position;
		_position = 0;
	}

	void halt() 
	{ 
		if (_status != Status::Halted && _status != Status::Manual) 
		{
			_status_before_halt = _status; 
			_status = Status::Halted;
		}
	}

	void resume() 
	{ 
		if (_status == Status::Halted)
			_status = _status_before_halt;
	}

	void enableManual(bool en = true);

	void setManualUpSpeed(float speed, float duration) 
	{
		if (_status == Status::Manual)
		{
			_value = speed * -1.f;
			_manual_duration = duration;
			_timer.reset();
		}
	}
	
	void setManualDownSpeed(float speed, float duration)
	{
		if (_status == Status::Manual) 
		{
			_value = speed;
			_manual_duration = duration;
			_timer.reset();
		}
	} 

private:
	bool _en;
	volatile float _manual_duration;

	volatile Status _status;
	Status _status_before_halt;

	uint16_t _prev_currents[W_CURRENT_BUFFER_SIZE];
	volatile uint32_t _buf_index = 0;
	volatile uint32_t _current_sum = 0;

	volatile float _target;
	volatile float _position;
	volatile float _value = 0.f;

	MotorSpeedControl _motor;
	
	mbed::Ticker _cur_ticker;
	mbed::Ticker _pos_ticker;
	mbed::Timer _timer;

	void m_motorPositionController();
	void m_motorCurrentSampler();

	float m_getPositionMeters()
	{
		return _motor.encoder().getTurnsFloat() * WINCH_PULLEY_DIAMETER * PI;
	}
};

#endif // WINCH_H_