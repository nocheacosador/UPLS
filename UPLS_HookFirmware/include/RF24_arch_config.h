/*
TMRh20 2015
ATTiny Configuration File
*/

#ifndef __RF24_ARCH_CONFIG_H__
#define __RF24_ARCH_CONFIG_H__

/*** USER DEFINES:  ***/
//#define FAILURE_HANDLING
//#define MINIMAL
/**********************/

#define rf24_max(a,b) (a>b?a:b)
#define rf24_min(a,b) (a<b?a:b)

#include <stddef.h>

// Include the header file for SPI functions ( Main SPI code is contained in RF24.cpp for simplicity )
#include "../lib/spi/spi.h"

#define _SPI SPI

#include <avr/pgmspace.h>

#define PRIPSTR "%S"

#endif // __RF24_ARCH_CONFIG_H__