
/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */
 
 /* spaniakos <spaniakos@gmail.com>
  Added __ARDUINO_X86__ support
*/

#ifndef __RF24_CONFIG_H__
#define __RF24_CONFIG_H__
  
  /**********************/
#define rf24_max(a,b) (a>b?a:b)
#define rf24_min(a,b) (a<b?a:b)

#if defined SPI_HAS_TRANSACTION && !defined SPI_UART && !defined SOFTSPI
#define RF24_SPI_TRANSACTIONS
#endif
 
   
#define RF24_TINY
#include "RF24_arch_config.h"

#endif // __RF24_CONFIG_H__

