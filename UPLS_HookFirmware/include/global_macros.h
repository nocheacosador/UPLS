/*
 * definitions.h
 *
 * Created: 8/27/2020 16:28:31
 *  Author: lukas
 */ 


#ifndef GLOBAL_MACROS_H
#define GLOBAL_MACROS_H

// Define this device for package configuration
// THIS_DEFINE values:
//		1 - xavier
//		2 - hook
//		3 - main controller

#define THIS_DEVICE				2
#define DEFAULT_RECEIVER_DEVICE	3

#ifndef 	__HOOK
# define	__HOOK
#endif


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

#define STATUS_REPORT_PERIOD		200
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

#define LATCH_PULSE_MIN		800
#define LATCH_PULSE_MAX		2200

#define LATCH_OVERCOMPENSATED_PULSE_DIF		100		// us
#define LATCH_OVERCOMPENSATED_PULSE_DUR		500		// ms
#define LATCH_NORMAL_PULSE_CHECK_DELAY_DUR	500		// ms
#define LATCH_RETRY_DELAY_DUR				1000	// ms
#define LATCH_CHECK_TRESHOLD_CURRENT		0.04f	// A
#define LATCH_MAX_RETRIES					5

const byte addresses[2][6] = { "10000", "20000" };

// EEPROM Addresses

#define EEPROM_LATCH_OPEN_PULSE_ADDR	(uint16_t*)(0x00)
#define EEPROM_LATCH_CLOSE_PULSE_ADDR	(uint16_t*)(0x02)

#endif /* GLOBAL_MACROS_H */