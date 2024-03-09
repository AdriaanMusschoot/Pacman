#include "Header/Time.h"

void Time::Update()
{
	const auto currentTimePoint = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<double>(currentTimePoint - m_PreviousTimePoint).count();
	m_PreviousTimePoint = currentTimePoint;
	if (m_DeltaTime > 1.0)
	{
		m_DeltaTime = 0.1;
	}
}

double Time::GetDeltaTime() const
{
	return m_DeltaTime;
}
