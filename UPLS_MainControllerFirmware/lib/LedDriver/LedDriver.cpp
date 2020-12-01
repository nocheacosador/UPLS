#include "LedDriver.h"

LedDriver::LedDriver(PinName pin, float update_rate = 50.0)
	: _en(false), _pwm_out(pin), _period(1.f / update_rate),
	 _mode(LedDriver::Mode::Normal), _value(0), _state(InternalState::OFF_VALUE),
	 _last_timepoint(0)
{
	_pwm_out.period_us(100);
	_pwm(_value);
}

void LedDriver::enable(bool enable = true)
{
	if (enable && !_en)
	{
		_tick.attach(this, &LedDriver::_handler, 1.f / _period);
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
	}
}

inline bool LedDriver::enable()
{
	return _en;
}

void LedDriver::mode(Mode mode)
{
	if (_mode != mode)
	{
		_mode = mode;
		_last_timepoint = _timer.read_ms();
	}
}

inline LedDriver::Mode LedDriver::mode()
{
	return _mode;
}

void LedDriver::turnOn()
{
	_on = true;
	_last_timepoint = _timer.read_ms();
}

void LedDriver::turnOff()
{
	_on = false;
	_last_timepoint = _timer.read_ms();
}

void LedDriver::settings(LedDriver::Settings settings)
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
			_value = static_cast<int>(_settings.on_value - _settings.off_value) * (_timer.read_ms() - _last_timepoint)
				/ int(_settings.fade_in_duration) + _settings.off_value;
			
			if (!_on)
			{
				_state = InternalState::FADING_OUT;
				_last_timepoint = _timer.read_ms();
			}
			else if (_value >= _settings.on_value)
			{
				_state = InternalState::ON_VALUE;
				_last_timepoint = _timer.read_ms();
			}
			break;

		case InternalState::FADING_OUT:
			_value = static_cast<int>(_settings.off_value - _settings.on_value) * (_timer.read_ms() - _last_timepoint)
				/ int(_settings.fade_out_duration) + _settings.on_value;
			
			if (_value <= _settings.off_value)
			{
				_value = _settings.off_value;
				_state = InternalState::OFF_VALUE;
				_last_timepoint = _timer.read_ms();
			}
			break;

		case InternalState::ON_VALUE:
			_value = _settings.on_value;

			if (_timer.read_ms() - _last_timepoint >= _settings.on_duration)
			{
				_state = InternalState::FADING_OUT;
				_last_timepoint = _timer.read_ms();
			}
			break;

		case InternalState::OFF_VALUE:
			_value = _settings.off_value;

			if (_timer.read_ms() - _last_timepoint >= _settings.off_duration && _on)
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
			_value = static_cast<int>(_settings.on_value - _settings.off_value) * (_timer.read_ms() - _last_timepoint)
				/ int(_settings.fade_in_duration) + _settings.off_value;
			
			if (_value >= _settings.on_value)
			{
				_value = _settings.on_value;
				_state = InternalState::ON_VALUE;
				_last_timepoint = _timer.read_ms();
			}
			break;

		case InternalState::FADING_OUT:
			_value = static_cast<int>(_settings.off_value - _settings.on_value) * (_timer.read_ms() - _last_timepoint)
				/ int(_settings.fade_out_duration) + _settings.on_value;
			
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
		break;

	default:
		_value = 0;
	}

	_pwm(_value);
}

inline void LedDriver::_pwm(uint8_t val)
{
	_pwm_out.write(float(_value) / 255.f);
}