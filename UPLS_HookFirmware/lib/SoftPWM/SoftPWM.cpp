/* 
* SoftPWM.cpp
*
* Created: 8/28/2020 11:40:08
* Author: lukas
*/


#include "SoftPWM.h"

#define PORTA_ADR		0x1B
#define PORTB_ADR		0x18

#define REGISTER(x)		_SFR_IO8((x))

Servo& Servo::assignPin(PinName pin)
{
	if (static_cast<uint8_t>(pin) < 8)
		m_port = PORTA_ADR;
	else
		m_port = PORTB_ADR;	
	
	m_pinNumber = static_cast<uint8_t>(pin) % 8;
	
	REGISTER(m_port - 1) |=  (static_cast<uint8_t>(1) << static_cast<uint8_t>(m_pinNumber));
	
	REGISTER(m_port) &= ~(1 << m_pinNumber);
	
	m_TCCR1B_val  = (1 << WGM12) | (1 << CS11);
	
	TIMSK1 |= (1 << OCIE1B) | (1 << OCIE1A);
	
	OCR1A = 20000;
	OCR1B = LATCH_PULSE_MIN;

	sei();

	return *this;
}

ISR (TIM1_COMPA_vect)
{
	Servo::instance().OCR1A_Handler();
}

ISR (TIM1_COMPB_vect)
{
	Servo::instance().OCR1B_Handler();
}
