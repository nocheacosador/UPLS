#ifndef __RF24_CONFIG_H__
#define __RF24_CONFIG_H__
  
  /**********************/
#define rf24_max(a,b) (a>b?a:b)
#define rf24_min(a,b) (a<b?a:b)
#define _BV(x)        (1 << x)

#include <stddef.h>

#define RF24_TINY
//#include "RF24_arch_config.h"

#endif // __RF24_CONFIG_H__