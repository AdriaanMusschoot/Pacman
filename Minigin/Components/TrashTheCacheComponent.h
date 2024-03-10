#pragma once
#include "Base/Component.h"
#include <vector>
#include <chrono>
#include <future>

namespace amu
{
	class GameObject;

	class TrashTheCacheEx1 final : public Component
	{
	public:
		TrashTheCacheEx1(GameObject* ownerObjectPtr);
		~TrashTheCacheEx1() override = default;

		TrashTheCacheEx1(const TrashTheCacheEx1& other) = delete;
		TrashTheCacheEx1(TrashTheCacheEx1&& other) = delete;
		TrashTheCacheEx1& operator=(const TrashTheCacheEx1& other) = delete;
		TrashTheCacheEx1& operator=(TrashTheCacheEx1&& other) = delete;

		void Update() override;
	private:
		std::vector<int> m_IntVec{};
		std::vector<float> m_TimingVec{};
		std::vector<float> m_IntervalVec{ { 1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f, 64.0f, 128.0f, 252.0f, 512.0f, 1024.0f } };
		int m_SampleCount{ 10 };

		std::promise<void> m_Promise;
		std::future<void> m_Future;

		bool m_Calculating{ false };
		bool m_GraphReady{ false };
		void TestEx1();
		void DrawPlot();
	};

}