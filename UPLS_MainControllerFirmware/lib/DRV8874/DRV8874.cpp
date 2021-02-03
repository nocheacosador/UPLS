#include "DRV8874.h"

#define MAX_DUTYCYCLE		0.8f

DRV8874::DRV8874(PinName inputPin1, PinName inputPin2, PinName sleepPin, PinName adcPin, float Ripropi)
	: m_in1(inputPin1), m_in2(inputPin2), m_slp(sleepPin), m_adc(adcPin), m_automaticBraking(false), 
	  m_resistor(Ripropi)
{
	m_slp.period_us(DRV8874_PWM_PERIOD_US);

	stop();
}

/* Set duty cycle of control signal and rotation direction;
 * Positive values - clockwise;
 * Negative values - counterclockwise.
*/
void DRV8874::turn(float speed)
{
	if (speed < 0.f)
	{
#ifdef MOTOR_REVERSE	
		m_in1 = 0;
		m_in2 = 1;
#else 
		m_in1 = 1;
		m_in2 = 0;
#endif
		speed *= -1.f;
		m_slp.write((speed >= MAX_DUTYCYCLE) ? 1.f : speed);
	}
	else if (speed > 0.f)
	{
#ifdef MOTOR_REVERSE	
		m_in1 = 1;
		m_in2 = 0;
#else 
		m_in1 = 0;
		m_in2 = 1;
#endif
		m_slp.write((speed >= MAX_DUTYCYCLE) ? 1.f : speed);
	}
	else
	{
		if (m_automaticBraking)
		{
			brake();
			return;
		}
		else 
		{
			stop();
			return;
		}
	}
}

void DRV8874::turnCW(float speed)
{
	if (speed <= 0.f) 
	{
		if (m_automaticBraking)
		{
			brake();
			return;
		}
		else 
		{
			stop();
			return;
		}
	}
	m_slp.write((speed >= MAX_DUTYCYCLE) ? 1.f : speed);

#ifdef MOTOR_REVERESE	
		m_in1 = 1;
		m_in2 = 0;
#else 
		m_in1 = 0;
		m_in2 = 1;
#endif
}

void DRV8874::turnCCW(float speed)
{
	if (speed <= 0.f) 
	{
		if (m_automaticBraking)
		{
			brake();
			return;
		}
		else 
		{
			stop();
			return;
		}
	}
	m_slp.write((speed >= MAX_DUTYCYCLE) ? 1.f : speed);

#ifdef MOTOR_REVERESE	
		m_in1 = 0;
		m_in2 = 1;
#else 
		m_in1 = 1;
		m_in2 = 0;
#endif
}

float DRV8874::getCurrent()
{
	return m_adc.getRmsFloat() * ADC_V_REF / m_resistor / 0.00045f;
}

DRV8874_Proper::DRV8874_Proper(PinName inputPin1, PinName inputPin2, PinName sleepPin, PinName adcPin, float Ripropi)
	: m_in1(inputPin1), m_in2(inputPin2), m_slp(sleepPin), m_adc(adcPin), m_automaticBraking(false), 
	  m_resistor(Ripropi)
{
	m_in1.period_us(DRV8874_PROPER_PWM_PERIOD_US);
	m_in2.period_us(DRV8874_PROPER_PWM_PERIOD_US);

	stop();
}

/* Set duty cycle of control signal and rotation direction;
 * Positive values - clockwise;
 * Negative values - counterclockwise.
*/
void DRV8874_Proper::turn(float speed)
{
	if (speed == 0.0f)
	{
		if (m_automaticBraking)
		{
			brake();
			return;
		}
		else 
		{
			stop();
			return;
		}
	}
	else
	{
		if (speed > 1.f) speed = 1.f;
		else if (speed < -1.f) speed = -1.f;
		
		m_slp = 1;
#ifdef MOTOR_REVERSE	
		m_in1 = ( speed >= 0.f ? speed        : 0.f );
		m_in2 = ( speed <  0.f ? speed * -1.f : 0.f );
#else 
		m_in2 = ( speed >= 0.f ? speed        : 0.f );
		m_in1 = ( speed <  0.f ? speed * -1.f : 0.f );
#endif
	}

	m_speed = speed;
}

void DRV8874_Proper::turnCW(float speed)
{
	if (speed <= 0.f) 
	{
		if (m_automaticBraking)
		{
			brake();
			return;
		}
		else 
		{
			stop();
			return;
		}
	}
	m_slp = 1;

#ifdef MOTOR_REVERESE	
		m_in1 = speed;
		m_in2 = 0.f;
#else 
		m_in1 = 0.f;
		m_in2 = speed;
#endif
}

void DRV8874_Proper::turnCCW(float speed)
{
	if (speed <= 0.f) 
	{
		if (m_automaticBraking)
		{
			brake();
			return;
		}
		else 
		{
			stop();
			return;
		}
	}
	m_slp = 1;

#ifdef MOTOR_REVERESE	
		m_in1 = 0.f;
		m_in2 = speed;
#else 
		m_in1 = speed;
		m_in2 = 0.f;
#endif
}

float DRV8874_Proper::getCurrent()
{
	return m_adc.getRmsFloat() * ADC_V_REF / m_resistor / 0.00045f;
}