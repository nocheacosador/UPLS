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
#include "Packet.h"

class Latch
{
public:
	typedef typename HookInfo::Latch::State  State;
	
	Latch(PinName servo_pin, DifferentialADC::Channel adc_ch);

	void open();
	void close();
	void turnOff();
	void turnOn();
	
	float getCurrent();

	void setOpenPulseDuration(uint16_t pulse);
	void setClosePulseDuration(uint16_t pulse);

	bool handle(Error* err);

	State getStatus() { return _stat; }
	uint16_t getOpenPulseDuration() { return _open_pulse_duration; }
	uint16_t getClosePulseDuration() { return _close_pulse_duration; }

private:
	enum class InternalState : uint8_t 
	{
		open,
		closing_overcompensated_pulse,
		closing_normal_pulse,
		closing_retry_open,
		closed,
		opening_overcompensated_pulse,
		opening_normal_pulse,
		opening_retry_close
	};
	
	Latch( const Latch &c ) = delete;
	Latch& operator=( const Latch &c ) = delete;

	uint16_t _open_pulse_duration;
	uint16_t _close_pulse_duration;

	State _stat;
	DifferentialADC _adc;

	uint32_t _next_time_point;
	InternalState _int_stat;
	uint8_t  _retries;
};

#endif //__LATCH_H__
