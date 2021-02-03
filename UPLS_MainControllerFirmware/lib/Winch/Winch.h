
#ifndef WINCH_H_
#define WINCH_H_

#include "../../include/global_macros.h"
#include "../MotorSpeedControl/MotorSpeedControl.h"
#include "../Extruder/Extruder.h"
#include "../Packet/packet.h"
#include <Timer.h>
#include <Ticker.h>
#include <cmath>

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
			if (_status == Status::Docking)
			{
				_motor.resetPid();
				_motor.enable(true);
			}
			_status = Status::GoingHome;
			_target = 0.f;
			_value = 0.0f;
		}
	}
	void lower(float value = LOWEST_POINT)
	{
		if (_status != Status::Halted && _status != Status::Manual)
		{
			if (_status == Status::Docking)
			{
				_motor.resetPid();
				_motor.enable(true);
			}
			_status = Status::Lowering;
			_target = value;
			_value = 0.0f;
		}
	}	

	float getPosition() { return _position; }
	
	uint16_t getCurrent() { return uint16_t(_motor.getCurrent() * 1000.f); }

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
			if (_status == Status::Docking)
			{
				_motor.resetPid();
				_motor.enable(true);
			}
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

	volatile float _target;
	volatile float _position;
	volatile float _value = 0.f;

	int _docking_counter = 0;

	MotorSpeedControl _motor;
	Extruder _extruder;

	mbed::Ticker _pos_ticker;
	mbed::Timer _timer;

	void m_motorPositionController();

	float m_getPositionMeters()
	{
		return _motor.encoder().getTurnsFloat() * WINCH_PULLEY_DIAMETER * PI;
	}

	float m_extruderTransferFunction(float winch_speed)
	{
		static constexpr float LOG2 = std::log(2.f);

		if (winch_speed == 0.f)
			return 0.f;
		else if (winch_speed > 0.f)
			return std::log(winch_speed) / LOG2 / 7.f;
		else if (winch_speed < 0.f)
			return std::log(winch_speed * -1.f) / LOG2 / -20.f;
	}
};
#endif // WINCH_H_