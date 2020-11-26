/*
 * cxa_guard.cpp
 *
 * Created: 8/28/2020 13:17:09
 *  Author: lukas
 */ 

#include "cxa_guard.h"

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {}; 