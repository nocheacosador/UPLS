#pragma once 

#include "../../include/global_macros.h"
#include <DigitalIn.h>
#include <InterruptIn.h>
#include <Timer.h>
#include <Timeout.h>

#define ENCODER_RPM_ENABLE

inline int64_t my_pow(int64_t base, uint8_t power)
{
	int64_t result = 1;
	for (uint8_t i = 0; i < power; i++)
		result *= base;
	return result;
}

class Encoder
{
public:
	enum class Rotation { CW = 1, CCW = 2, NONE = 0 };

	Encoder(PinName A, PinName B, int cpr = 2096);

	float getAngle() const
	{
    	return float(m_steps) / float(m_stepsPerRev) * TWO_PI; 
	}

	int getTurns(uint8_t fixed_point = 0) const
	{
		int64_t multiplier = 1;
		
		if (fixed_point == 6)
			multiplier = 1000000;
		else
			multiplier = my_pow(10, fixed_point);

		return int(int64_t(m_steps) * multiplier / m_stepsPerRev);
	}

	float getTurnsFloat() const
	{
		return float(m_steps) / float(m_stepsPerRev);
	}

	int getSteps() const
	{
		return m_steps;
	}

	void reset() 
	{ 
		m_steps = 0;
	}

private:
	mbed::InterruptIn m_a;
	mbed::InterruptIn m_b;

	volatile int m_stepsPerRev;
	volatile int m_steps;

	void m_aRiseHandler();
	void m_aFallHandler();
	void m_bRiseHandler();
	void m_bFallHandler();
};