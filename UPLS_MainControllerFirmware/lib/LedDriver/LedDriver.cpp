#include "LedDriver.h"

#define LIMIT(x, max, min) 	((((x >= max) ? max : x) <= min ) ? min : x)

LedDriver::LedDriver(PinName pin, float update_rate)
	: _en(false), _pwm_out(pin), _period(1.f / update_rate),
	 _mode(LedDriver::Mode::Normal), _value(0), _state(InternalState::OFF_VALUE),
	 _last_timepoint(0)
{
	_pwm_out.period_us(100);
	_pwm(_value);
}

void LedDriver::enable(bool enable)
{
	if (enable && !_en)
	{
		_tick.attach(this, &LedDriver::_handler, _period);
		_en = true;
		_timer.start();
		_last_timepoint = _timer.read_ms();
		_state = InternalState::OFF_VALUE;
	}
	else if (_en)
	{
		_tick.detach();
		_timer.stop();
		_en = false;
		_value = 0;
		_pwm(0);
	}
}

void LedDriver::mode(Mode mode)
{
	if (_mode != mode)
	{
		_mode = mode;
		_last_timepoint = _timer.read_ms();
	}
}

void LedDriver::turnOn()
{
	_last_timepoint = _timer.read_ms();
	_on = true;
}

void LedDriver::turnOff()
{
	if (_state == InternalState::ON_VALUE)
	{
		__disable_irq();
		_state = InternalState::FADING_OUT;
		_on = false;
		_last_timepoint = _timer.read_ms();
		__enable_irq();
	}
	else if (_state == InternalState::FADING_IN)
	{
		__disable_irq();
		_state = InternalState::FADING_OUT;
		_on = false;
		
		int dt = int(_settings.fade_out_duration) - (int(_settings.fade_out_duration)
			 * (int(_value) - int(_settings.off_value)) / (int(_settings.on_value) 
			 - int(_settings.off_value)));
		
		_last_timepoint = _timer.read_ms() - dt;

		__enable_irq();
	}
	else
		_on = false;
}

void LedDriver::settings(const LedDriver::Settings& settings)
{
	_settings = settings;
}

LedDriver::Settings LedDriver::settings()
{
	return _settings;
}

uint8_t LedDriver::value()
{
	return _value;
}

void LedDriver::_handler()
{
	int delta_time = _timer.read_ms() - _last_timepoint;
	int temp;

	switch (_mode)
	{
	case LedDriver::Mode::Normal:
		if(_on)
		{
			_state = InternalState::ON_VALUE;
			_value = _settings.on_value;
		}
		else
		{
			_state = InternalState::OFF_VALUE;
			_value = _settings.off_value;
		}
		break;

	case LedDriver::Mode::Pulsing:
		switch (_state)
		{
		case InternalState::FADING_IN:
			temp = int(_settings.on_value - _settings.off_value) * delta_time
				/ int(_settings.fade_in_duration) + int(_settings.off_value);
			
			_value = uint8_t(LIMIT(temp, _settings.on_value, _settings.off_value));

			if (delta_time >= _settings.fade_out_duration)
			{
				_last_timepoint = _timer.read_ms();
				_state = InternalState::ON_VALUE;
			}
			break;

		case InternalState::FADING_OUT:
			temp = int(_settings.on_value - _settings.off_value) 
				* (int(_settings.fade_in_duration) - delta_time)
				/ int(_settings.fade_in_duration) + int(_settings.off_value);
			
			_value = uint8_t(LIMIT(temp, _settings.on_value, _settings.off_value));

			if (delta_time >= _settings.fade_out_duration)
			{
				_value = _settings.off_value;
				_last_timepoint = _timer.read_ms();
				_state = InternalState::OFF_VALUE;
			}
			break;

		case InternalState::ON_VALUE:
			_value = _settings.on_value;

			if (delta_time >= _settings.on_duration)
			{
				_state = InternalState::FADING_OUT;
				_last_timepoint = _timer.read_ms();
			}
			break;

		case InternalState::OFF_VALUE:
			_value = _settings.off_value;

			if (delta_time >= _settings.off_duration && _on)
			{
				_state = InternalState::FADING_IN;
				_last_timepoint = _timer.read_ms();
			}
			break;
		}

		break;
	
	case LedDriver::Mode::Soft:
		switch (_state)
		{
		case InternalState::FADING_IN:
			temp = int(_settings.on_value - _settings.off_value) * delta_time
				/ int(_settings.fade_in_duration) + int(_settings.off_value);
			
			_value = uint8_t(LIMIT(temp, _settings.on_value, _settings.off_value));
			
			if (_value >= _settings.on_value)
			{
				_value = _settings.on_value;
				_state = InternalState::ON_VALUE;
				_last_timepoint = _timer.read_ms();
			}
			break;

		case InternalState::FADING_OUT:
			temp = int(_settings.on_value - _settings.off_value) 
				* (int(_settings.fade_in_duration) - delta_time)
				/ int(_settings.fade_in_duration) + int(_settings.off_value);
			
			_value = uint8_t(LIMIT(temp, _settings.on_value, _settings.off_value));
			
			if (_value <= _settings.off_value)
			{
				_value = _settings.off_value;
				_state = InternalState::OFF_VALUE;
				_last_timepoint = _timer.read_ms();
			}
			break;

		case InternalState::ON_VALUE:
			_value = _settings.on_value;

			if (!_on)
			{
				_state = InternalState::FADING_OUT;
				_last_timepoint = _timer.read_ms();
			}
			break;

		case InternalState::OFF_VALUE:
			_value = _settings.off_value;

			if (_on)
			{
				_state = InternalState::FADING_IN;
				_last_timepoint = _timer.read_ms();
			}
			break;
		}
		break;

	default:
		_value = 0;
		break;
	}

	_pwm(_value);
}

inline void LedDriver::_pwm(uint8_t val)
{
	_pwm_out.write(float(255 - val) / 255.f);
}