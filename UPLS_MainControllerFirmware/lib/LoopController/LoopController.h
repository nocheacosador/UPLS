#ifndef LOOPCONTROLLER_H_
#define LOOPCONTROLLER_H_

#include <platform/NonCopyable.h>
#include "drivers/Timer.h"

class LoopController : mbed::NonCopyable<LoopController>
{
public:
	LoopController(float loop_frequency = 1000.f);

	float getUtilization();

	void handle();

private:
	int _period;
	int _lastLoopTime;
	int _pastTimePoint;

	mbed::Timer _timer;
};

#endif