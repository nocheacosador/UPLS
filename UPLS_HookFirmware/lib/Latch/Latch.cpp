/* 
* Latch.cpp
*
* Created: 10/5/2020 10:43:37
* Author: lukas
*/


#include "Latch.h"
#include "Timer0.h"
#include <avr/eeprom.h>

#define servo	Servo::instance()

Latch::Latch(PinName servo_pin, DifferentialADC::Channel adc_ch) 
	: _adc(adc_ch, DifferentialADC::Gain::x20, DifferentialADC::Reference::INT),
	_next_time_point(0), _retries(0)
{
	uint16_t memory_read_pulse = eeprom_read_word(EEPROM_LATCH_OPEN_PULSE_ADDR);
	
	if (memory_read_pulse >= LATCH_PULSE_MIN && memory_read_pulse <= LATCH_PULSE_MAX)
	{
		_open_pulse_duration = memory_read_pulse;
	}
	else
	{
		_open_pulse_duration = SERVO_OPEN_PULSE_DURATION;
		eeprom_update_word(EEPROM_LATCH_OPEN_PULSE_ADDR, SERVO_OPEN_PULSE_DURATION);
	}

	memory_read_pulse = eeprom_read_word(EEPROM_LATCH_CLOSE_PULSE_ADDR);

	if (memory_read_pulse >= LATCH_PULSE_MIN && memory_read_pulse <= LATCH_PULSE_MAX)
	{
		_close_pulse_duration = memory_read_pulse;
	}
	else
	{
		_close_pulse_duration = SERVO_CLOSE_PULSE_DURATION;
		eeprom_update_word(EEPROM_LATCH_CLOSE_PULSE_ADDR, SERVO_CLOSE_PULSE_DURATION);
	}

	servo.assignPin(servo_pin).enable(true);

	close();
}

void Latch::setOpenPulseDuration(uint16_t pulse)
{
	if (pulse < LATCH_PULSE_MIN)
		pulse = LATCH_PULSE_MIN;
	else if (pulse > LATCH_PULSE_MAX)
		pulse = LATCH_PULSE_MAX;
	
	_open_pulse_duration = pulse;
	eeprom_update_word(EEPROM_LATCH_OPEN_PULSE_ADDR, pulse);
}

void Latch::setClosePulseDuration(uint16_t pulse)
{
	if (pulse < LATCH_PULSE_MIN)
		pulse = LATCH_PULSE_MIN;
	else if (pulse > LATCH_PULSE_MAX)
		pulse = LATCH_PULSE_MAX;
	
	_close_pulse_duration = pulse;
	eeprom_update_word(EEPROM_LATCH_CLOSE_PULSE_ADDR, pulse);
}

void Latch::open()
{
	servo.pulse(_open_pulse_duration + LATCH_OVERCOMPENSATED_PULSE_DIF);

	_next_time_point = millis() + LATCH_OVERCOMPENSATED_PULSE_DUR;
	_int_stat = InternalState::opening_overcompensated_pulse;
	_stat = State::Opening;
}

void Latch::close()
{
	servo.pulse(_close_pulse_duration - LATCH_OVERCOMPENSATED_PULSE_DIF);
	
	_next_time_point = millis() + LATCH_OVERCOMPENSATED_PULSE_DUR;
	_int_stat = InternalState::closing_overcompensated_pulse;
	_stat = State::Closing;
}

void Latch::turnOff()
{
	servo.enable(false);
}

void Latch::turnOn()
{
	servo.enable(true);
}

float Latch::getCurrent()
{
	return _adc.readVoltage() / CURRENT_SENSE;
}

bool Latch::handle(Error* err)
{
	bool ok = true;
	
	switch (_int_stat)
	{
	case InternalState::closing_overcompensated_pulse:
		if (millis() >= _next_time_point)
		{
			servo.pulse(_close_pulse_duration);
			_int_stat = InternalState::closing_normal_pulse;
			_next_time_point = millis() + LATCH_NORMAL_PULSE_CHECK_DELAY_DUR;
		}
		break;

	case InternalState::closing_normal_pulse:
		if (millis() >= _next_time_point)
		{
			if (getCurrent() >= LATCH_CHECK_TRESHOLD_CURRENT)
			{
				if (_retries < LATCH_MAX_RETRIES)
				{
					servo.pulse(_open_pulse_duration);
					_int_stat = InternalState::closing_retry_open;
					_next_time_point = millis() + LATCH_RETRY_DELAY_DUR;
					_retries++;
				}
				else
				{
					open();
					ok = false;
					err->code = Error::LatchFailedToClose;
					_retries = 0;
				}
			}
			else
			{
				_int_stat = InternalState::closed;
				_stat = State::Closed;
				_retries = 0;
			}
		}
		break;
	
	case InternalState::closing_retry_open:
		if (millis() >= _next_time_point)
			close();
		break;

	case InternalState::closed:
		if (servo.getPulseLength() != _close_pulse_duration)
			close();
		break;

	case InternalState::opening_overcompensated_pulse:
		if (millis() >= _next_time_point)
		{
			servo.pulse(_open_pulse_duration);
			_int_stat = InternalState::opening_normal_pulse;
			_next_time_point = millis() + LATCH_NORMAL_PULSE_CHECK_DELAY_DUR;
		}
		break;

	case InternalState::opening_normal_pulse:
		if (millis() >= _next_time_point)
		{
			if (getCurrent() >= LATCH_CHECK_TRESHOLD_CURRENT)
			{
				if (_retries < LATCH_MAX_RETRIES)
				{
					servo.pulse(_close_pulse_duration);
					_int_stat = InternalState::opening_retry_close;
					_next_time_point = millis() + LATCH_RETRY_DELAY_DUR;
					_retries++;
				}
				else
				{
					close();
					ok = false;
					err->code = Error::LatchFailedToOpen;
					_retries = 0;
				}
			}
			else
			{
				_int_stat = InternalState::open;
				_stat = State::Open;
				_retries = 0;
			}
		}
		break;
	
	case InternalState::opening_retry_close:
		if (millis() >= _next_time_point)
			open();
		break;	

	case InternalState::open:
		if (servo.getPulseLength() != _open_pulse_duration)
			open();
		break;
	}
	
	return ok;
}