#ifndef LEDDRIVER_H_
#define LEDDRIVER_H_

#include <PinNames.h>
#include <PwmOut.h>
#include <Ticker.h>
#include <Timer.h>
#include <UARTSerial.h>
#include "packet.h"

class LedDriver
{
public:
	typedef typename LedInfo::Led::Mode Mode;
	typedef typename LedInfo::Led::Settings Settings;
	
	/*struct Settings
	{
		uint8_t on_value;
		uint8_t off_value;
		uint16_t on_duration;
		uint16_t off_duration;
		uint16_t fade_in_duration;
		uint16_t fade_out_duration;

		Settings(uint8_t onValue = 255, uint8_t offValue = 0, uint16_t onDuration = 1000,
			uint16_t offDuration = 1000, uint16_t fadeInDuration = 1000,
			uint16_t fadeOutDuration = 1000) 
			: on_value(onValue), off_value(offValue), on_duration(onDuration), off_duration(offDuration),
			  fade_in_duration(fadeInDuration), fade_out_duration(fadeOutDuration) { ; }
	};*/

	LedDriver(PinName pin, float update_rate = 50.f);

	void enable(bool enable = true);

	bool isEnabled() { return _en; }

	void mode(Mode mode);

	Mode getMode() { return _mode; }

	void turnOn();

	void turnOff();

	void settings(const Settings& settings);

	Settings settings();

	uint8_t value();

private:
	volatile bool _en;
	volatile bool _on;
	volatile Mode _mode;
	float _period;
	volatile uint8_t _value;
	volatile int _last_timepoint;

	mbed::PwmOut _pwm_out;
	mbed::Ticker _tick;
	mbed::Timer _timer;
	Settings _settings;

	void _handler();
	void _pwm(uint8_t val);

	enum class InternalState
	{
		ON_VALUE,
		OFF_VALUE,
		FADING_IN,
		FADING_OUT
	};

	volatile InternalState _state;
};

#endif