/* 
* ADC.h
*
* Created: 9/18/2020 23:10:53
* Author: lukas
*/


#ifndef __ADC_H__
#define __ADC_H__

#include "Pin.h"

class SingleADC
{
public:
	enum class Channel : uint8_t
	{
	// Single Ended Channels:
		ADC0 = 0x00,
		ADC1 = 0x01,
		ADC2 = 0x02,
		ADC3 = 0x03,
		ADC4 = 0x04,
		ADC5 = 0x05,
		ADC6 = 0x06,
		ADC7 = 0x07,

		AGND = 0x20,
		IREF = 0x21,

		ADC8 = 0x22,
		TEMP = ADC8
	};

	enum class Reference : uint8_t
	{
		VCC = 0x00,
		EXT = 0x40,
		INT = 0x80
	};
	
	SingleADC(Channel channel, Reference voltage_reference = Reference::VCC);

	void setTopVoltage(float voltage)
	{
		top_voltage = voltage;
	}

	float readVoltage()
	{
		return float(read()) / 1024.f * top_voltage;
	}

	uint16_t read();

private:
	SingleADC( const SingleADC &c ) = delete;
	SingleADC& operator=( const SingleADC &c ) = delete;

	uint8_t ADMUX_val;
	float	top_voltage;
};


class DifferentialADC
{
public:
	enum class Channel : uint8_t
	{
		ADC3_ADC2 = 0x30
	};

	enum class Gain : uint8_t
	{
		x1	= 0x00,
		x20 = 0x01
	};

	enum class Reference : uint8_t
	{
		VCC = 0x00,
		EXT = 0x40,
		INT = 0x80
	};

	DifferentialADC(Channel channel, Gain gain = Gain::x1, Reference voltage_reference = Reference::VCC);

	uint16_t read();

	void setTopVoltage(float voltage)
	{
		top_voltage = voltage;
	}

	float readVoltage()
	{
		return float(read()) / 1024.f * top_voltage / ((ADMUX_val & (1 << MUX0)) ? 20.f : 1.f);
	}

private:
	DifferentialADC( const DifferentialADC &c ) = delete;
	DifferentialADC& operator=( const DifferentialADC &c ) = delete;

	uint8_t ADMUX_val;
	float	top_voltage;
};


#endif //__ADC_H__
