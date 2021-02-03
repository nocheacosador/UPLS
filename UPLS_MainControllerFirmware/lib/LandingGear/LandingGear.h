#ifndef LANDINGGEAR_H_
#define LANDINGGEAR_H_

#include "../../include/global_macros.h"
#include "DRV8874.h"
#include "packet.h"
#include <Ticker.h>
#include <Timer.h>

#define LG_CURRENT_BUFFER_SIZE  		20
#define UP_TRANSIT_CURRENT_TRESHOLD		600
#define DOWN_TRANSIT_CURRENT_TRESHOLD	600
#define LG_UP_DUTY_CYCLE				-0.5f
#define LG_DOWN_DUTY_CYCLE				0.5f

class LandingGear
{
public:
	class Leg
	{
	public:
		typedef typename LandingGearInfo::Leg::Status  Status;

		Leg(PinName inputPin1, PinName inputPin2, PinName sleepPin, PinName adcPin, float Ripropi = 1.f);
		
		void retract() { if (_en) _status = Status::InUpTransit; }
		void extract() { if (_en) _status = Status::InDownTransit; }
		void enable(bool en);

		uint16_t getCurrent() { return uint16_t(_motor.getCurrent()); }
		uint8_t getValue() { return uint8_t(abs(_value * 255.f)); }
		Status getStatus() { return _status; }

	private:
		void _handler();
		void _current_monitor();
		
		bool _en;

		volatile float _value;
		volatile Status _status;

		mbed::Ticker _ticker;
		mbed::Timer _timer;
		DRV8874 _motor;
	};
	
	LandingGear();

	void extract();
	void retract();

	Leg front;
	Leg rear;
};

#endif // LANDINGGEAR_H_