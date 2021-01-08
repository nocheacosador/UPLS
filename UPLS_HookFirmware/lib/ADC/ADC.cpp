/* 
* ADC.cpp
*
* Created: 9/18/2020 23:10:53
* Author: lukas
*/


#include "ADC.h"
#include "../../include/global_macros.h"

static bool adc_initialized = false;

void init_ADC()
{
	if (!adc_initialized)
	{
#if F_CPU == 8000000UL
		ADCSRA = 0x04;
#elif F_CPU <= 1000000UL
		ADCSRA = 0x03;
#else
	#error "Prescaler could not be determined."
#endif

		adc_initialized = true;
	}
}

SingleADC::SingleADC(Channel channel, Reference voltage_reference) : top_voltage(0.f)
{
	ADMUX_val = static_cast<uint8_t>(voltage_reference) | static_cast<uint8_t>(channel);

	if (voltage_reference == Reference::INT)
		top_voltage = V_REF1V1;

	init_ADC();
}

uint16_t SingleADC::read()
{
	ADCSRA &= ~(1 << ADEN);
	
	ADMUX = ADMUX_val;

	// dummy read
	ADCSRA |= (1 << ADEN) | (1 << ADSC);
	while (ADCSRA & (1 << ADSC)) { ; }
	
	// actual measurement
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC)) { ; }
	uint16_t res = ADC;

	ADCSRA &= ~(1 << ADEN);
	
	return res;
}

DifferentialADC::DifferentialADC(DifferentialADC::Channel channel, 
								 DifferentialADC::Gain gain, 
								 DifferentialADC::Reference voltage_reference)
	 : top_voltage(0.f)
{
	ADMUX_val =  static_cast<uint8_t>(voltage_reference) | static_cast<uint8_t>(channel) | static_cast<uint8_t>(gain);

	if (voltage_reference == Reference::INT)
		top_voltage = V_REF1V1;

	init_ADC();
}

uint16_t DifferentialADC::read()
{
	ADCSRA &= ~(1 << ADEN);
	
	ADMUX = ADMUX_val;


	// dummy read
	ADCSRA |= (1 << ADEN) | (1 << ADSC);
	while (ADCSRA & (1 << ADSC)) { ; }
	
	// actual measurement
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC)) { ; }
	uint16_t res = ADC;

	ADCSRA &= ~(1 << ADEN);
	
	return res;
}