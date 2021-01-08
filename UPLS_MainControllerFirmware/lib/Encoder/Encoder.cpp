#include "Encoder.h"

#include <Callback.h>

using namespace mbed;

Encoder::Encoder(PinName A, PinName B, int StepsPerRevolution) : m_a(A), m_b(B), m_stepsPerRev(StepsPerRevolution), 
    m_steps(0)
{
	m_a.rise(callback(this, &Encoder::m_aRiseHandler));
	m_b.rise(callback(this, &Encoder::m_bRiseHandler));

	//m_a.fall(callback(this, &Encoder::m_aFallHandler));
	//m_b.fall(callback(this, &Encoder::m_bFallHandler));
}

void Encoder::m_aRiseHandler()
{
	if (m_b.read())
	{
		m_steps--;
	}
	else
	{
        m_steps++;
	}
}

void Encoder::m_aFallHandler()
{
    if (m_b.read())
    {
        m_steps++;
    }
    else
    {
        m_steps--;
    }
}

void Encoder::m_bRiseHandler()
{
    if (m_a.read())
	{
        m_steps++;
	}
    else
    {
        m_steps--;
    }
}

void Encoder::m_bFallHandler()
{
    if (m_a.read())
    {
        m_steps--;
    }
    else
    {
        m_steps++;
    }
}
