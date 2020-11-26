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
	_check(0), _check_time(0), _retries(0)
{
	uint16_t memory_read_pulse = eeprom_read_word(EEPROM_LATCH_OPEN_PULSE_ADDR);
	
	if (memory_read_pulse >= PULSE_MIN && memory_read_pulse <= PULSE_MAX)
	{
		_open_pulse_duration = memory_read_pulse;
	}
	else
	{
		_open_pulse_duration = SERVO_OPEN_PULSE_DURATION;
		eeprom_update_word(EEPROM_LATCH_OPEN_PULSE_ADDR, SERVO_OPEN_PULSE_DURATION);
	}

	memory_read_pulse = eeprom_read_word(EEPROM_LATCH_CLOSE_PULSE_ADDR);

	if (memory_read_pulse >= PULSE_MIN && memory_read_pulse <= PULSE_MAX)
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
	if (pulse < PULSE_MIN)
		pulse = PULSE_MIN;
	else if (pulse > PULSE_MAX)
		pulse = PULSE_MAX;
	
	_open_pulse_duration = pulse;
	eeprom_update_word((uint16_t*)EEPROM_LATCH_OPEN_PULSE_ADDR, pulse);
}

void Latch::setClosePulseDuration(uint16_t pulse)
{
	if (pulse < PULSE_MIN)
		pulse = PULSE_MIN;
	else if (pulse > PULSE_MAX)
		pulse = PULSE_MAX;
	
	_close_pulse_duration = pulse;
	eeprom_update_word(EEPROM_LATCH_CLOSE_PULSE_ADDR, pulse);
}

void Latch::open()
{
	servo.pulse(_open_pulse_duration);

	_stat = State::OPEN;
}

void Latch::close()
{
	servo.pulse(_close_pulse_duration);
	
	_check_time = millis() + LATCH_CHECK_DELAY;
	_check = 1;
	//_retry = false;
	_stat = State::CLOSING;
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

bool Latch::handle()
{
	bool no_error = true;

	switch (_stat)
	{
	case State::OPEN:
		if (servo.getPulseLength() != _open_pulse_duration)
			open();
		break;

	case State::CLOSED:
		if (servo.getPulseLength() != _close_pulse_duration)
			close();
		break;

	case State::CLOSING:
		if (millis() >= _check_time && _check == 1)
		{
			if (getCurrent() >= LATCH_CHECK_TRESHOLD_CURRENT)
			{
				if (_retries < LATCH_MAX_RETRIES)
				{
					// open to reattempt closing
					servo.pulse(_open_pulse_duration);
					_retries++;
					//_retry = true;
					_check = 2;
					_check_time = millis() + LATCH_RETRY_DELAY;
				}
				else
				{
					no_error = false;
					_retries = 0;
					//_retry = false;
					_check = 0;
					open();
				}
			}
			else
			{
				_retries = 0;
				_check = 0;
				_stat = State::CLOSED;
			}
		}
		else if (millis() >= _check_time && _check == 2)
		{
			close();
		}

		break;

	case State::OPENING:
		
		break; 
	}

	return no_error;
}