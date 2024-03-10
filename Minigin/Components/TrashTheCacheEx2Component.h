#pragma once
#include "Base/Component.h"
#include <vector>
#include <chrono>
#include <future>


namespace amu
{
	struct Transform
	{
		float matrix[16] =
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	};

	class GameObject3D
	{
	public:
		Transform local;
		int id;
	};

	class GameObject3DAlt
	{
	public:
		Transform* local;
		int id;
	};


	class TrashTheCacheEx2 final : public Component
	{
	public:
		TrashTheCacheEx2(GameObject* ownerObjectPtr);
		~TrashTheCacheEx2() override = default;

		TrashTheCacheEx2(const TrashTheCacheEx2& other) = delete;
		TrashTheCacheEx2(TrashTheCacheEx2&& other) = delete;
		TrashTheCacheEx2& operator=(const TrashTheCacheEx2& other) = delete;
		TrashTheCacheEx2& operator=(TrashTheCacheEx2&& other) = delete;

		void Update() override;
	private:
		std::vector<GameObject3D> m_GameObject3DVec{};
		std::vector<GameObject3DAlt> m_GameObject3DAltVec{};
		bool m_CalculatingNormal{};
		bool m_CalculatingAlternative{};
		std::vector<float> m_TimingNormalVec{};
		std::vector<float> m_TimingAlternativeVec{};
		std::vector<float> m_IntervalVec{ { 1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f, 64.0f, 128.0f, 252.0f, 512.0f, 1024.0f } };
		int m_SampleCount{ 10 };

		std::promise<void> m_PromiseNormal;
		std::future<void> m_FutureNormal;
		std::promise<void> m_PromiseAlternative;
		std::future<void> m_FutureAlternative;

		bool m_GraphNormalReady{ false };
		bool m_GraphAlternativeReady{ false };

		void TestEx2Alt();

		void TestEx2();

		void DrawPlot();
	};

}