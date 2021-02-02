#ifndef EXTRUDER_H_
#define EXTRUDER_H_

#include "../../include/global_macros.h"
#include <PwmOut.h>
#include <DigitalOut.h>

class Extruder
{
public:
	Extruder(PinName in1, PinName in2);

	/* Positive values - extrude
	 * Negative values - retract
	 * Zero - stop()
	*/
	void turn(float speed)
	{
		if (speed > 0.f)
		{
			extrude(speed);
		}
		else if (speed < 0.f)
		{
			retract(speed * -1.f);
		}
		else
		{
			stop();
		}
	}
	
	void extrude(float speed = 1.f)
	{
		m_pwm = 1.f - speed;
		m_dir = 0;
	}
	
	void retract(float speed = 1.f)
	{
		m_pwm = 1.f - speed;
		m_dir = 1;
	}
	
	void stop()
	{
		m_pwm = 1.f;
	}

private:
	mbed::PwmOut m_pwm;
	mbed::DigitalOut m_dir;
};

#endif // EXTRUDER_H_