#include "LoopController.h"

LoopController::LoopController(float loop_frequency) 
	: _period(int(1000000.f / loop_frequency)), _lastLoopTime(0)
{
	_timer.start();
	_pastTimePoint = _timer.read_us();
}

float LoopController::getUtilization()
{
	return float(_lastLoopTime) / float(_period) * 100.f;
}

void LoopController::handle()
{
	int now = _timer.read_us();
	_lastLoopTime = now - _pastTimePoint;
	while (now - _pastTimePoint < _period) { now = _timer.read_us(); }
	_pastTimePoint = now;
}
