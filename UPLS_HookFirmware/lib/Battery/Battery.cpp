/* 
* Battery.cpp
*
* Created: 10/5/2020 16:11:28
* Author: lukas
*/


#include "Battery.h"


Battery::Battery(SingleADC::Channel channel, PinName charging_pin) 
	: _charging_pin(charging_pin, INPUT), _adc(channel, SingleADC::Reference::VCC)
{
	_adc.setTopVoltage(V_REF2V8);
}
