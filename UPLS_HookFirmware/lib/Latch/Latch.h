/* 
* Latch.h
*
* Created: 10/5/2020 10:43:37
* Author: lukas
*/


#ifndef __LATCH_H__
#define __LATCH_H__


#include "ADC.h"
#include "SoftPWM.h"


class Latch
{
public:
	enum State : uint8_t
	{
		OPEN    = 0x2F,
		CLOSED  = 0x1F,
		CLOSING = 0x0F,
		OPENING = 0x3F
		//ERROR   = 0xFF
	};
	
	Latch(PinName servo_pin, DifferentialADC::Channel adc_ch);

	void open();
	void close();
	void turnOff();
	void turnOn();
	
	float getCurrent();

	void setOpenPulseDuration(uint16_t pulse);
	void setClosePulseDuration(uint16_t pulse);

	bool handle();

	State getStatus()
	{
		return _stat;
	}

private:
	Latch( const Latch &c ) = delete;
	Latch& operator=( const Latch &c ) = delete;

	uint16_t _open_pulse_duration;
	uint16_t _close_pulse_duration;

	State _stat;
	DifferentialADC _adc;

	uint32_t _check_time;
	//uint32_t _retry_time;
	uint8_t	 _check;
	//bool	 _retry;
	uint8_t  _retries;
};

#endif //__LATCH_H__
