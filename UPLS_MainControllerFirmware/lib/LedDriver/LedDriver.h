#ifndef LEDDRIVER_H_
#define LEDDRIVER_H_

#include <PinNames.h>
#include <PwmOut.h>
#include <Ticker.h>
#include <Timer.h>

class LedDriver
{
public:
	enum class Mode
	{
		Normal = 1,
		Soft,
		Pulsing
	};

	struct Settings
	{
		uint8_t on_value = 255.f;
		uint8_t off_value = 0.f;
		uint16_t on_duration = 1000.f;
		uint16_t off_duration = 1000.f;
		uint16_t fade_in_duration = 1000.f;
		uint16_t fade_out_duration = 1000.f;

		Settings() { ; }
	};

	LedDriver(PinName pin, float update_rate = 50.0);

	void enable(bool enable = true);

	bool enable();

	void mode(Mode mode);

	Mode mode();

	void turnOn();

	void turnOff();

	void settings(Settings settings);

	Settings settings();

	uint8_t value();

private:
	bool _en;
	bool _on;
	bool _fadingIn;
	Mode _mode;
	float _period;
	uint8_t _value;
	int _last_timepoint;

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

	InternalState _state;
};

#endif