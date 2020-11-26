/*
 * cxa_guard.h
 *
 * Created: 8/28/2020 13:16:49
 *  Author: lukas
 */ 


#ifndef CXA_GUARD_H_
#define CXA_GUARD_H_

__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);

#endif /* CXA_GUARD_H_ */