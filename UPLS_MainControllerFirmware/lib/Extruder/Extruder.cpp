#include "Extruder.h"

Extruder::Extruder(PinName dir, PinName pwm) :
	m_pwm(pwm), m_dir(dir)
{
	stop();
}