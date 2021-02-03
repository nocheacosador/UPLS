#ifndef MOTORSPEEDCONTROL_H_
#define MOTORSPEEDCONTROL_H_

#include "../../include/global_macros.h"
#include "Encoder.h"
#include "DRV8874.h"
#include <Ticker.h>

class MotorSpeedControl
{
public:
	MotorSpeedControl() : _mot(WINCH_MOTOR_IN1, WINCH_MOTOR_IN2, WINCH_MOTOR_SLP, WINCH_MOTOR_ADC, WINCH_MOTOR_R_IPROPI),
		_enc(WINCH_MOTOR_ENCODER_A, WINCH_MOTOR_ENCODER_B, WINCH_MOTOR_ENCODER_SPR) 
		{ ; }

	void enable(bool en)
	{
		if (en)
		{
			_pid_ticker.attach(this, &MotorSpeedControl::pid, dt);
		}
		else
		{
			_pid_ticker.detach();
		}
		
	}

	float getSetSpeed()
	{
		return _target_speed;
	}

	float getSpeed()
	{
		return _actual_speed;
	}

	void speed(float rpm)
	{
		_target_speed = rpm;
		if (rpm == 0)
		{
			_integral_term = 0.0f;
		}
	}

	float getCurrent()
	{
		return _mot.getCurrent();
	}

	Encoder& encoder()
	{
		return _enc;
	}

	DRV8874_Proper& motor()
	{
		return _mot;
	}

private:
	DRV8874_Proper _mot;
	Encoder _enc;
	mbed::Ticker  _pid_ticker;

	float _error = 0.0f;
	float _target_speed = 0.0f;
	float _actual_speed = 0.0f;
	float _integral_term = 0.0f;
	float _prev_err = 0.0f;
	float _prev_pos = 0.0f;
	float _value = 0.f;
	const float dt = 0.05f;

	void pid();
};

#endif // MOTORSPEEDCONTROL_H_