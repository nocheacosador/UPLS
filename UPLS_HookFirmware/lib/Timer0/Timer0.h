/*
 * Timer0.h
 *
 * Created: 9/11/2020 16:59:58
 *  Author: lukas
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#define OVERFLOW_PERIOD_US	2048

#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile uint32_t __overflow_count;

void init_timer0(void);

inline uint32_t millis(void)
{
	return (OVERFLOW_PERIOD_US * __overflow_count + TCNT0 * 8) / 1000;
}

inline uint64_t micros(void)
{
	return (OVERFLOW_PERIOD_US * __overflow_count + TCNT0 * 8);
}

#endif /* TIMER0_H_ */