#include "spi.h"

#define _BV(x) (1 << x)

void SPIClass::begin()
{
	//pinMode(USCK, OUTPUT);
	//pinMode(DO, OUTPUT);
	//pinMode(DI, INPUT);

	DDRA |= _BV(DDA4);
	DDRA |= _BV(DDA5);
	DDRA &= ~_BV(DDA6);

	USICR = _BV(USIWM0);
}

uint8_t SPIClass::transfer(uint8_t b)
{
	USIDR = b;
	USISR = _BV(USIOIF);
	
	do
	USICR = _BV(USIWM0) | _BV(USICS1) | _BV(USICLK) | _BV(USITC);
	while ((USISR & _BV(USIOIF)) == 0);
	
	return USIDR;
}

void SPIClass::end() { ; }
void SPIClass::setDataMode(uint8_t mode) { ; }
void SPIClass::setBitOrder(uint8_t bitOrder) { ; }
void SPIClass::setClockDivider(uint8_t rate) { ; }