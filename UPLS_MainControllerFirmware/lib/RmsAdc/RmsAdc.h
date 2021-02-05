#ifndef RMSADC_H_
#define RMSADC_H_

#include <AnalogIn.h>
#include <Ticker.h>
#include <cmath>

static inline uint16_t sqrt_c(const uint32_t a_nInput)
{
	if (a_nInput & 0x80000000) return 0;
	uint32_t op  = a_nInput;
	uint32_t res = 0;
	uint32_t one = 1uL << 30; // The second-to-top bit is set: use 1u << 14 for uint16_t type; use 1uL<<30 for uint32_t type
	// "one" starts at the highest power of four <= than the argument.
	while (one > op)
	    one >>= 2;
	while (one != 0)
	{
	    if (op >= res + one)
	    {
	        op = op - (res + one);
	        res = res +  2 * one;
	    }
	    res >>= 1;
	    one >>= 2;
	}
	return res;
}

template<uint32_t sample_count>
class RmsAdc
{
public:
	RmsAdc(PinName adc_pin, us_timestamp_t sample_period = 1004) :
		m_adc(adc_pin)
	{
		m_tick.attach_us(this, &RmsAdc::m_currentSampler, sample_period);
		for (uint32_t i = 0; i < sample_count; i++) m_samples[i] = 0;
	}

	float getRmsFloat()
	{
		return m_sampleSum / float(sample_count);
	}

private:
	mbed::AnalogIn m_adc;
	mbed::Ticker   m_tick;

	volatile float m_sampleSum = 0;
	
	float m_samples[sample_count];
	uint32_t m_sampleIndex = 0;

	void m_currentSampler()
	{
		m_sampleSum -= m_samples[m_sampleIndex];
		m_samples[m_sampleIndex] = m_adc.read();
		m_sampleSum += m_samples[m_sampleIndex];
		m_sampleIndex++;
		m_sampleIndex %= sample_count;
	}
}; 

typedef RmsAdc<50> DefaultRmsAdc;

#endif // RMSADC_H_