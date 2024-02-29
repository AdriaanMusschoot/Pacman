#pragma once

#include <chrono>

#include "Singleton.h"

class Time final : public dae::Singleton<Time>
{
public:
	void Update();

	double GetDeltaTime() const;
private:
	friend class Singleton<Time>;
	Time() = default;
	std::chrono::high_resolution_clock::time_point m_PreviousTimePoint;

	double m_DeltaTime{ 0 };
	double m_FixedTimeStep{ 0.02 };
};