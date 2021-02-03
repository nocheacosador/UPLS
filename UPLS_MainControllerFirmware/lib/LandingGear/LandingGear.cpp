#include "LandingGear.h"

LandingGear::Leg::Leg(PinName inputPin1, PinName inputPin2, PinName sleepPin, PinName adcPin, float Ripropi)
	: _en(false), _value(0.f),
	 _status(Status::Unknown),
	 _motor(inputPin1, inputPin2, sleepPin, adcPin, Ripropi)
{
}

void LandingGear::Leg::enable(bool en)
{
	if (en && !_en)
	{
		_en = true;
		_status = Status::InDownTransit;
		_ticker.attach(this, &LandingGear::Leg::_handler, 0.1f);
	}
	else if (_en)
	{
		_ticker.detach();
		_motor.stop();
		_value = 0.0;
		_status = Status::Unknown;
		_en = false;
	}
}

void LandingGear::Leg::_handler()
{
	switch (_status)
	{
	case Status::Up:
		_value = 0.0f;
		break;

	case Status::Down:
		_value = 0.f;
		break;

	case Status::InUpTransit:
		if (getCurrent() >= UP_TRANSIT_CURRENT_TRESHOLD)
		{
			_value = 0.f;
			_status = Status::Up;
		}
		else
			_value = LG_UP_DUTY_CYCLE;
		break;

	case Status::InDownTransit:
		if (getCurrent() >= DOWN_TRANSIT_CURRENT_TRESHOLD)
		{
			_value = 0.f;
			_status = Status::Down;
		}
		else
			_value = LG_DOWN_DUTY_CYCLE;
		break;

	default:
		_status = Status::InDownTransit;
		break;
	}

	_motor.turn(_value);
}
		
	
LandingGear::LandingGear()
	: front(LEG_MOT_FRONT_IN1, LEG_MOT_FRONT_IN2, 
			LEG_MOT_FRONT_SLP, LEG_MOT_FRONT_ADC, 
			LEG_MOT_FRONT_R_IPROPI),
	  rear(LEG_MOT_REAR_IN1, LEG_MOT_REAR_IN2, 
		   LEG_MOT_REAR_SLP, LEG_MOT_REAR_ADC, 
		   LEG_MOT_REAR_R_IPROPI)
{ ; }

void LandingGear::extract()
{
	front.extract();
	rear.extract();
}

void LandingGear::retract()
{
	front.retract();
	rear.retract();
}
