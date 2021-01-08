/* 
* Battery.h
*
* Created: 10/5/2020 16:11:28
* Author: lukas
*/


#ifndef __BATTERY_H__
#define __BATTERY_H__

#include "ADC.h"
#include "Pin.h"
#include "../../include/global_macros.h"

#include "Packet.h"

class Battery
{
public:
	typedef typename HookInfo::Battery::State State;
	
	Battery(SingleADC::Channel channel, PinName charging_pin = PinName::NC);

	State getState()
	{
		if (_charging_pin.read() == 0)
			return State::Charging;
		else if (_charging_pin.read() == 1)
			return State::Discharging;
		else 
			return State::Unknown;
	}

	uint16_t getVoltage()
	{
		 return uint16_t(_adc.readVoltage() * 1000.f * BAT_MEAS_R_C);
	}

private:
	Battery( const Battery &c );
	Battery& operator=( const Battery &c );
	
	Pin _charging_pin;
	SingleADC _adc;
};

#endif //__BATTERY_H__
