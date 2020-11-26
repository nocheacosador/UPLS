/*
 * definitions.h
 *
 * Created: 8/27/2020 16:28:31
 *  Author: lukas
 */ 


#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define F_CPU	8000000UL

#define _BV(x)	(1 << x)

#define __DELAY_BACKWARD_COMPATIBLE__

#include <util/delay.h>

#define delay(x)				_delay_ms(x)
#define delayMicroseconds(x)	_delay_us(x)

typedef uint8_t	byte;

// Commands

#define CMD_STATUS_REQUEST		's'
#define CMD_LATCH_OPEN		    '1'
#define CMD_LATCH_CLOSE         '2'

// Config

#define STATUS_REPORT_PERIOD		1000
#define RETRY_BUFFER_SIZE			6

// Hardware parameters

//#define V_REF				1.132f
#define V_REF1V1			1.0471f
#define V_REF2V8			2.800f

// resistor divider coefficient
#define BAT_MEAS_R_C		2.02985f

#define CURRENT_SENSE		0.22f // Ohms

// default params
#define SERVO_OPEN_PULSE_DURATION		1800	// us
#define SERVO_CLOSE_PULSE_DURATION		1200	// us
#define BATTERY_WARNING_VOLTAGE			3600	// mV
#define BATTERY_EMPTY_VOLTAGE			3300	// mV
#define BATTERY_CHECK_PERIOD			100		// ms
#define BATTERY_EMPTY_TRESHOLD_COUNTER	10

#define PULSE_MIN		700
#define PULSE_MAX		2500

#define LATCH_CHECK_DELAY				400		// ms
#define LATCH_RETRY_DELAY				1500	// ms
#define LATCH_CHECK_TRESHOLD_CURRENT	0.03f	// A
#define LATCH_MAX_RETRIES				5

const byte addresses[2][6] = { "10000", "20000" };

// EEPROM Addresses

#define EEPROM_LATCH_OPEN_PULSE_ADDR	(uint16_t*)0x00
#define EEPROM_LATCH_CLOSE_PULSE_ADDR	(uint16_t*)0x02


#endif /* DEFINITIONS_H_ */