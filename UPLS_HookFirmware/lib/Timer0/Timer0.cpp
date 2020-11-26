/*
 * Timer0.cpp
 *
 * Created: 9/16/2020 14:14:09
 *  Author: lukas
 */ 

#include "Timer0.h"

volatile uint32_t __overflow_count = 0;

void init_timer0(void)
{
	TCCR0B |= (1 << CS01) | (1 << CS00);
	TIMSK0 |= (1 << TOIE0);
	TCNT0 = 0;

	sei();
}

ISR (TIM0_OVF_vect)
{
	__overflow_count++;
}