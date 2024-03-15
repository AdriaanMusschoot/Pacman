#pragma once

#include <chrono>

#include "Singleton.h"

class GameTime final : public amu::Singleton<GameTime>
{
public:
	void Update();

	double GetDeltaTime() const;
private:
	friend class Singleton<GameTime>;
	GameTime() = default;
	std::chrono::high_resolution_clock::time_point m_PreviousTimePoint;

	double m_DeltaTime = 0;
};