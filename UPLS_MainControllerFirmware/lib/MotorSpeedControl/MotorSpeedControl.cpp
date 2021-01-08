#include "MotorSpeedControl.h"

void MotorSpeedControl::pid()
{
	float pos = _enc.getTurnsFloat();
	_actual_speed = (pos - _prev_pos) / dt * 60.f;
	_prev_pos = pos;
	_error = _target_speed - _actual_speed;

	// proportional term
	float proportional_term = PID_KP * _error;

	// integral term
	_integral_term += PID_KI * _error * dt;

	if (_integral_term > 1.f) _integral_term = 1.f;
	else if (_integral_term < -1.f) _integral_term = -1.f;
	
	// derivative term
	float temp = (_error - _prev_err) / dt;
	float derivative_term = PID_KD * temp;

	//float pid_output = proportional_term + integral_term + derivative_term;

	_value = proportional_term + _integral_term + derivative_term;

	if (_value > 1.f) _value = 1.f;
	else if (_value < -1.f) _value = -1.f;

	if (_target_speed == 0.0f && abs(_actual_speed) < 1.0f)
		_mot.brake();
	else
		_mot.turn(_value);
	
	_prev_err = _error;
}