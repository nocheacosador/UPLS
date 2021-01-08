#ifndef FILTERS_H_
#define FILTERS_H_

namespace Filters
{
	namespace FirstOrder
	{
		class LowPass
		{
		public:
			LowPass() : m_prevous(0.f), m_default_dt(1.f), m_rc(1.f) { ; }

			void setDefaultDT(const float dt)
			{
				m_default_dt = dt;
			}

			void setTimeConstant(const float rc)
			{
				m_rc = rc;
			}

			const float filter(const float& value, float dt = 0.f)
			{
				if (!dt)
					dt = m_default_dt;

				m_prevous = m_prevous + (dt / (m_rc + dt)) * (value - m_prevous);
				return m_prevous;
			}
		
		private:
			float m_prevous;
			float m_default_dt;
			float m_rc;
		};
	};
};

#endif // FILTERS_H_