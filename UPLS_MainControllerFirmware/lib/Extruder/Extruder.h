#ifndef EXTRUDER_H_
#define EXTRUDER_H_

#include "../../include/global_macros.h"
#include <PwmOut.h>

class Extruder
{
public:
	Extruder(PinName in1, PinName in2);

	/* Positive values - extrude
	 * Negative values - retract
	 * Zero - stop()
	*/
	void turn(float speed);
	void extrude(float speed = 1.f);
	void retract(float speed = 1.f);
	void stop();

private:
	mbed::PwmOut m_in1;
	mbed::PwmOut m_in2;
};

#endif // EXTRUDER_H_