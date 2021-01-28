#include "Extruder.h"

Extruder::Extruder(PinName in1, PinName in2) :
	m_in1(in1), m_in2(in2)
{
	stop();
}

void Extruder::extrude(float speed)
{
	m_in1 = speed;
	m_in2 = 0.f; 
}

void Extruder::retract(float speed)
{
	m_in2 = speed;
	m_in1 = 0.f;
}

void Extruder::stop()
{
	m_in1 = 0.f;
	m_in2 = 0.f;
}

void Extruder::turn(float speed)
{
	if (speed > 0.f)
	{
		m_in1 = speed;
		m_in2 = 0.f; 
	}
	else if (speed < 0.f)
	{
		m_in2 = speed;
		m_in1 = 0.f;
	}
	else
	{
		m_in1 = 0.f;
		m_in1 = 0.f;
	}
	
}