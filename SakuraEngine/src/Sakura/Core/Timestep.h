#pragma once

namespace Sakura
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			:m_Time(time)
		{
		}

		operator float() const { return m_Time; }

		float GetTime() const { return m_Time; }
		float GetMilliTime() const { return m_Time * 1000; }
	private:
		float m_Time;
	};
}