/* 
* SoftPWM.h
*
* Created: 8/28/2020 11:40:08
* Author: lukas
*
*
* This class allows user to use any pin on AtTiny84 as PWM pin.
* It utilizes Timer1 for that.
*
*
*
*
*
*
*/

#ifndef __SOFTPWM_H__
#define __SOFTPWM_H__

#include "../../include/definitions.h"
#include "Pin.h"
#include "../../include/Singleton.h"
#include "cxa_guard.h"

#define PORTA_ADR		0x1B
#define PORTB_ADR		0x18

#define REGISTER(x)		_SFR_IO8((x))

class Servo : public Singleton<Servo>
{
private:
	friend Singleton;

	uint8_t m_pinNumber;
	uint8_t m_port;

	uint8_t m_TCCR1B_val;
	
	Servo() { ; }

public:
	Servo(Servo const&) = delete;
	Servo& operator=(Servo const&) = delete;
	
	Servo& assignPin(PinName pin);

	void enable(bool enable);

	void pulse(uint16_t pulse_duration_us)
	{
		if (pulse_duration_us > PULSE_MAX)
			pulse_duration_us = PULSE_MAX;
		else if (pulse_duration_us < PULSE_MIN)
			pulse_duration_us = PULSE_MIN;
		
		OCR1B = pulse_duration_us;
	}
	
	uint16_t getPulseLength()
	{
		return OCR1B;
	}

	// interrupt handlers
	
	void OCR1A_Handler()
	{
//#ifdef SERVO_INVERSE		
		REGISTER(m_port) &= ~(1 << m_pinNumber);
//#else
		//REGISTER(m_port) |= (1 << m_pinNumber);
//#endif	
	}
	
	void OCR1B_Handler()
	{
//#ifdef SERVO_INVERSE
		REGISTER(m_port) |= (1 << m_pinNumber);		
//#else
		//REGISTER(m_port) &= ~(1 << m_pinNumber);
//#endif
	}
};

#undef PORTA_ADR
#undef PORTB_ADR
#undef REGISTER

#endif //__SOFTPWM_H__
