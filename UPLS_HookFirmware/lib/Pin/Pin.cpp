/* 
* Pin.cpp
*
* Created: 8/27/2020 16:30:25
* Author: lukas
*/


#include "Pin.h"

#define PORTA_ADR		0x1B
#define PORTB_ADR		0x18

#define REGISTER(x)		_SFR_IO8((x))

//Pin::Pin() : m_pinNumber(0xFF) { ; }

Pin::Pin(PinName pin, PinMode mode)
{
	if (pin == NONE) 
	{
		m_pinNumber = 0xFF;
	}
	else
	{ 
		if (static_cast<uint8_t>(pin) < 8)
			m_port = PORTA_ADR;
		else
			m_port = PORTB_ADR;

		m_pinNumber = static_cast<uint8_t>(pin) % 8;

		REGISTER(m_port - 1) &= ~(1 << m_pinNumber);
		REGISTER(m_port - 1) |= (static_cast<uint8_t>(mode) << m_pinNumber);
	}
}