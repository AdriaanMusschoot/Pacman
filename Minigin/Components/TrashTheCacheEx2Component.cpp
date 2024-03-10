#include "TrashTheCacheEx2Component.h"

#include "Base/GameObject.h"
#include "imgui.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <thread>
#include "imgui_plot.h"

amu::TrashTheCacheEx2::TrashTheCacheEx2(GameObject* ownerObjectPtr)
	: Component(ownerObjectPtr)
{

}

void amu::TrashTheCacheEx2::Update()
{
	ImGui::Begin("Exercise 2");

	ImGui::InputInt("# samples", &m_SampleCount, 10);

	if (!m_CalculatingNormal)
	{
		if (ImGui::Button("Trash the cash with GameObject3D"))
		{
			m_PromiseNormal = std::promise<void>();
			m_FutureNormal = m_PromiseNormal.get_future();

			std::thread myThread(&TrashTheCacheEx2::TestEx2, this);

			myThread.detach();
			m_CalculatingNormal = true;
			m_GraphNormalReady = false;
		}
	}
	else
	{
		ImGui::Text("Wait for it...");
	}
	if (m_FutureNormal.valid() && m_FutureNormal.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
	{
		m_GraphNormalReady = true;
	}
	if (!m_CalculatingAlternative)
	{
		if (ImGui::Button("Trash the cash with GameObject3DAlt"))
		{
			m_PromiseAlternative = std::promise<void>();
			m_FutureAlternative = m_PromiseAlternative.get_future();

			std::thread myThread(&TrashTheCacheEx2::TestEx2Alt, this);

			myThread.detach();
			m_CalculatingAlternative = true;
			m_GraphAlternativeReady = false;
		}
	}
	else
	{
		ImGui::Text("Wait for it...");
	}
	if (m_FutureAlternative.valid() && m_FutureAlternative.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
	{
		m_GraphAlternativeReady = true;
	}

	DrawPlot();

	ImGui::End();
}

void amu::TrashTheCacheEx2::TestEx2Alt()
{
	m_GameObject3DAltVec.clear();
	m_TimingAlternativeVec.clear();
	m_GameObject3DAltVec.resize(static_cast<int>(std::pow(2, 26)));

	for (const float& stepSize : m_IntervalVec)
	{
		std::vector<float> durationVec;

		for (int idx{}; idx < m_SampleCount; ++idx)
		{
			auto timePointBefore = std::chrono::high_resolution_clock::now();

			for (int i{}; i < m_GameObject3DAltVec.size(); i += static_cast<int>(stepSize))
			{
				m_GameObject3DAltVec[i].id *= 2;
			}
			auto timePointAfter = std::chrono::high_resolution_clock::now();

			const auto duration{ std::chrono::duration_cast<std::chrono::microseconds>(timePointAfter - timePointBefore).count() };

			durationVec.emplace_back(static_cast<float>(duration));
		}
		const int timing = static_cast<int>(std::accumulate(durationVec.begin(), durationVec.end(), 0.0f)) / static_cast<int>(durationVec.size());
		const float fltTiming = static_cast<float>(timing);

		m_TimingAlternativeVec.emplace_back(fltTiming);

		std::cout << fltTiming << "\n";
	}
	m_PromiseAlternative.set_value();
	m_CalculatingAlternative = false;
}

void amu::TrashTheCacheEx2::TestEx2()
{
	m_GameObject3DVec.clear();
	m_TimingNormalVec.clear();
	m_GameObject3DVec.resize(static_cast<int>(std::pow(2, 26)));

	for (const float& stepSize : m_IntervalVec)
	{
		std::vector<float> durationVec;

		for (int idx{}; idx < m_SampleCount; ++idx)
		{
			auto timePointBefore = std::chrono::high_resolution_clock::now();

			for (int i{}; i < m_GameObject3DVec.size(); i += static_cast<int>(stepSize))
			{
				m_GameObject3DVec[i].id *= 2;
			}
			auto timePointAfter = std::chrono::high_resolution_clock::now();

			const auto duration{ std::chrono::duration_cast<std::chrono::microseconds>(timePointAfter - timePointBefore).count() };

			durationVec.emplace_back(static_cast<float>(duration));
		}

		//delete 20% of results as they are either very low or very high
		for (int idx{}; idx < m_SampleCount / 10; ++idx)
		{
			durationVec.erase(std::ranges::min_element(durationVec));
			durationVec.erase(std::ranges::max_element(durationVec));
		}

		const int timing = static_cast<int>(std::accumulate(durationVec.begin(), durationVec.end(), 0.0f)) / static_cast<int>(durationVec.size());
		const float fltTiming = static_cast<float>(timing);

		m_TimingNormalVec.emplace_back(fltTiming);

		std::cout << fltTiming << "\n";
	}
	m_PromiseNormal.set_value();
	m_CalculatingNormal = false;
}

void amu::TrashTheCacheEx2::DrawPlot()
{
	ImGui::BeginChild(1);

	static uint32_t selection_start = 0, selection_length = 0;
	const ImU32 colors[2] = { ImColor(0, 255, 0), ImColor(255, 0, 0) };

	ImGui::PlotConfig conf;
	conf.values.xs = m_IntervalVec.data();

	conf.grid_y.show = true;

	conf.scale.min = 0;


	conf.tooltip.format = "x=%g, y=%g";
	conf.tooltip.show = true;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(200, 100);

	if (m_GraphNormalReady)
	{
		conf.values.count = static_cast<int>(m_TimingNormalVec.size());
		conf.values.ys = m_TimingNormalVec.data();
		conf.values.color = colors[0];
		conf.scale.max = m_TimingNormalVec[0];
		conf.grid_y.size = m_TimingNormalVec[0] / 5;
		conf.grid_y.size = conf.scale.max / 5;
		ImGui::Plot("plot1", conf);
	}
	if (m_GraphAlternativeReady)
	{
		conf.values.count = static_cast<int>(m_TimingAlternativeVec.size());
		conf.values.ys = m_TimingAlternativeVec.data();
		conf.values.color = colors[1];
		conf.scale.max = m_TimingAlternativeVec[0];
		conf.grid_y.size = m_TimingAlternativeVec[0] / 5;
		conf.grid_y.size = conf.scale.max / 5;
		ImGui::Plot("plot1", conf);
	}
	if (m_GraphAlternativeReady && m_GraphNormalReady)
	{
		const float* y_data[] = { m_TimingNormalVec.data(), m_TimingAlternativeVec.data() };
		conf.values.count = static_cast<int>(m_TimingNormalVec.size());
		conf.values.ys = nullptr;
		conf.values.ys_list = y_data;
		conf.values.ys_count = 2;
		conf.values.colors = colors;
		conf.scale.max = m_TimingNormalVec[0];
		conf.grid_y.size = conf.scale.max / 5;
		ImGui::Plot("plot1", conf);
	}

	ImGui::EndChild();
}
