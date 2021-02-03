#ifndef DRV8874_H_
#define DRV8874_H_

#include "../../include/global_macros.h"
#include "../RmsAdc/RmsAdc.h"
#include <DigitalOut.h>
#include <PwmOut.h>

#define MOTOR_REVERSE

/* **********************************************************************
 *                  DRV8874 PWM CONTROL MODE
 *  +--------+-----+-----+------+------+------------------------------+
 *  | nSLEEP | IN1 | IN2 | OUT1 | OUT2 |          DESCRIPTION         |
 *  +--------+-----+-----+------+------+------------------------------+
 *  |    0   |  X  |  X  | Hi-Z | Hi-Z | Sleep, (H-Bridge Hi-Z)       |
 *  +--------+-----+-----+------+------+------------------------------+
 *  |    1   |  0  |  0  | Hi-Z | Hi-Z | Coast, (H-Bridge Hi-Z)       |
 *  +--------+-----+-----+------+------+------------------------------+
 *  |    1   |  0  |  1  |   L  |   H  | Reverse, (OUT2 -> OUT1)      |
 *  +--------+-----+-----+------+------+------------------------------+
 *  |    1   |  1  |  0  |   H  |   L  | Forward, (OUT1 -> OUT2)      |
 *  +--------+-----+-----+------+------+------------------------------+
 *  |    1   |  1  |  1  |   L  |   L  | Brake, (Low-Side Slow Decay) |
 *  +--------+-----+-----+------+------+------------------------------+
 * 
 * This table is taken from Texas Instruments DRV8874-Q1 datasheet.
 */

class DRV8874 
{
public:
	DRV8874(PinName inputPin1, PinName inputPin2, PinName sleepPin, PinName adcPin, float Ripropi = 1.f);

	/* Set duty cycle of control signal and rotation direction;
	 * Positive values - clockwise;
	 * Negative values - counterclockwise.
	*/
	void turn(float speed);

	void turnCW(float speed = 1.f);
	
	void turnCCW(float speed = 1.f);
	
	void stop()
	{
		m_in1 = 0;
		m_in2 = 0;
		m_slp.write(1.f);
	}

	void brake()
	{
		m_in1 = 1;
		m_in2 = 1;
		m_slp.write(1.f);
	}

	void enableAutomaticBraking(bool enable = true)
	{
		m_automaticBraking = enable;
	}

	void sleep(bool enable)
	{
		m_slp.write((enable) ? 0.f : 1.f);
	}

	float getCurrent();

private:
	mbed::DigitalOut 	m_in1;
	mbed::DigitalOut 	m_in2;
	mbed::PwmOut		m_slp;
	DefaultRmsAdc		m_adc;
	
	bool 	m_automaticBraking;
	float 	m_resistor;
};

class DRV8874_Proper
{
public:
	DRV8874_Proper(PinName inputPin1, PinName inputPin2, PinName sleepPin, PinName adcPin, float Ripropi = 1.f);

	/* Set duty cycle of control signal and rotation direction;
	 * Positive values - clockwise;
	 * Negative values - counterclockwise.
	*/
	void turn(float speed);

	void turnCW(float speed = 1.f);
	
	void turnCCW(float speed = 1.f);
	
	void stop()
	{
		m_in1 = 0.f;
		m_in2 = 0.f;
		m_slp = 1;
	}

	void brake()
	{
		m_in1 = 1.f;
		m_in2 = 1.f;
		m_slp = 1;
	}

	void enableAutomaticBraking(bool enable = true)
	{
		m_automaticBraking = enable;
	}

	void sleep(bool enable)
	{
		m_slp.write((enable) ? 0.f : 1.f);
	}

	float getCurrent();

public:
	mbed::PwmOut	 	m_in1;
	mbed::PwmOut 		m_in2;
	mbed::DigitalOut	m_slp;
	DefaultRmsAdc		m_adc;
	
	bool 	m_automaticBraking;
	float 	m_resistor;
	float   m_speed = 0;
};

#endif // DRV8874_H_