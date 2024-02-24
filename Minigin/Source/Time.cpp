#include "Header/Time.h"

void Time::Update()
{
	const auto currentTimePoint = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<double>(currentTimePoint - m_PreviousTimePoint).count();
	m_PreviousTimePoint = currentTimePoint;
}

double Time::GetDeltaTime() const
{
	return m_DeltaTime;
}
