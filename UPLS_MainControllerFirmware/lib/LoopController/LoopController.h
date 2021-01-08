#ifndef LOOPCONTROLLER_H_
#define LOOPCONTROLLER_H_

#include <platform/NonCopyable.h>
#include <Timer.h>
#include "Buffer/MyBuffer.h"

#define PREVIOUS_LOOP_TIMES_BUFFER_SIZE		100

class LoopController : mbed::NonCopyable<LoopController>
{
public:
	LoopController(float loop_frequency = 1000.f);

	float getUtilization();

	void handle();

private:
	int _period;
	int _pastTimePoint;

	int _prevLoopTimes[PREVIOUS_LOOP_TIMES_BUFFER_SIZE];
	int _buf_index;
	int _loop_time_sum;

	mbed::Timer _timer;
};

#endif