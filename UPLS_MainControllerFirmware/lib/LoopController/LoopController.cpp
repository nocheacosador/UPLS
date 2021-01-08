#include "LoopController.h"

LoopController::LoopController(float loop_frequency) 
	: _period(int(1000000.f / loop_frequency)), _buf_index(0)
{
	memset(_prevLoopTimes, 0, sizeof(int) * PREVIOUS_LOOP_TIMES_BUFFER_SIZE);
	
	_timer.start();
	_pastTimePoint = _timer.read_us();
}

float LoopController::getUtilization()
{
	return float(_loop_time_sum) / float(PREVIOUS_LOOP_TIMES_BUFFER_SIZE) / float(_period) * 100.f;
}

void LoopController::handle()
{
	int now = _timer.read_us();
	int loop_time = now - _pastTimePoint;
	
	_loop_time_sum += loop_time;
	_loop_time_sum -= _prevLoopTimes[_buf_index];
	_prevLoopTimes[_buf_index] = loop_time;
	_buf_index++;
	_buf_index %= PREVIOUS_LOOP_TIMES_BUFFER_SIZE;

	while (now - _pastTimePoint < _period) { now = _timer.read_us(); }
	_pastTimePoint = now;
}
