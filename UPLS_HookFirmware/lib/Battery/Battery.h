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
#include "../../include/definitions.h"

class Battery
{
public:
	enum State : uint8_t
	{
		CHARGING = 0x1F,
		DISCHARGING = 0x2F,

		UNKNOWN = 0x0F
	};
	
	Battery(SingleADC::Channel channel, PinName charging_pin = PinName::NC);

	State getState()
	{
		if (_charging_pin.read() == 0)
			return State::CHARGING;
		else if (_charging_pin.read() == 1)
			return State::DISCHARGING;
		else 
			return State::UNKNOWN;
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
