/* 
* Pin.h
*
* Created: 8/27/2020 16:30:25
* Author: lukas
*/


/*
* AtTiny84 pinout:
*		
*											 +---U---+
*										VCC	 |1    14|  GND
*							  (PCINT8)	PB0  |2    13|  PA0	 (PCINT0, ADC0, AREF)
*							  (PCINT9)	PB1  |3    12|  PA1  (PCINT1, ADC1)
*					  (RESET, PCINT11)	PB3  |4    11|  PA2  (PCINT2, ADC2)
*				 (OC0A, INT0, PCINT10)	PB2  |5    10|  PA3  (PCINT3, ADC3)
*			  (OC0B, SS, ADC7, PCINT7)	PA7  |6     9|  PA4  (PCINT4, ADC4, SCK, USCK)
*  (MOSI, DI, SDA, OC1A, ADC6, PCINT6)	PA6  |7     8|  PA5  (PCINT5, ADC5, MISO, DO)
*											 +-------+
*
*
* 
*/

#ifndef __PIN_H__
#define __PIN_H__

#include <avr/io.h>

#define PORTA_ADR		0x1B
#define PORTB_ADR		0x18

#define REGISTER(x)		_SFR_IO8((x))

enum PinName : uint8_t
{
	PA_0 = 0,
	PA_1 = 1,
	PA_2 = 2,
	PA_3 = 3,
	PA_4 = 4,
	PA_5 = 5,
	PA_6 = 6,
	PA_7 = 7,
	PB_0 = 8,
	PB_1 = 9,
	PB_2 = 10,
	PB_3 = 11,
	
	MISO = PA_5,
	MOSI = PA_6,
	SCL	 = PA_4,
	
	/*ADC0 = PA_0,
	ADC1 = PA_1,
	ADC2 = PA_2,
	ADC3 = PA_3,
	ADC4 = PA_4,
	ADC5 = PA_5,
	ADC6 = PA_6,
	ADC7 = PA_7,*/

	NONE = 0xFF,
	NC = NONE
};

enum PinMode : uint8_t
{
	OUTPUT = 1,
	INPUT  = 0
};

class Pin
{	
private:
	uint8_t m_pinNumber;
	uint8_t m_port;

public:
	//Pin();
	Pin(PinName pin, PinMode mode = OUTPUT);

	int read()
	{
		if (m_pinNumber != 0xFF)
			return (REGISTER(m_port - 2) & (1 << m_pinNumber)) ? 1 : 0;
		else 
			return -1;
	}
	
	void write(uint8_t state)
	{
		if (m_pinNumber != 0xFF)
		{
			if (state >= 1)
				REGISTER(m_port) |= (1 << m_pinNumber);
			else
				REGISTER(m_port) &= ~(1 << m_pinNumber);
		}
	}

	void setMode(PinMode mode)
	{
		REGISTER(m_port - 1) &= ~(1 << m_pinNumber);
		REGISTER(m_port - 1) |=  (static_cast<uint8_t>(mode) << m_pinNumber);
	}

	Pin& operator()(uint8_t state)
	{
		if (m_pinNumber != 0xFF)
		{
			if (state >= 1)
				REGISTER(m_port) |= (1 << m_pinNumber);
			else
				REGISTER(m_port) &= ~(1 << m_pinNumber);
		}
		return *this;
	}
};

#undef PORTA_ADR
#undef PORTB_ADR

#undef REGISTER

#endif //__PIN_H__
