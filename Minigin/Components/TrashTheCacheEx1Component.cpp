#include "TrashTheCacheEx1Component.h"

#include "Base/GameObject.h"
#include "imgui.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <thread>
#include "imgui_plot.h"

void amu::TrashTheCacheEx1::TestEx1()
{
	m_IntVec.clear();
	m_TimingVec.clear();
	m_IntVec.resize(static_cast<int>(std::pow(2, 26)), 69);

	for (const float& stepSize : m_IntervalVec)
	{
		std::vector<float> durationVec;

		for (int idx{}; idx < m_SampleCount; ++idx)
		{
			auto timePointBefore = std::chrono::high_resolution_clock::now();
			for (int i{}; i < static_cast<int>(m_IntVec.size()); i += static_cast<int>(stepSize))
			{
				m_IntVec[i] *= 2;
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
		m_TimingVec.emplace_back(fltTiming);
		std::cout << fltTiming << "\n";
	}
	m_Promise.set_value();
	m_Calculating = false;
}

void amu::TrashTheCacheEx1::DrawPlot() const
{
	static uint32_t selection_start = 0, selection_length = 0;

	ImGui::BeginChild(1);

	ImGui::PlotConfig conf;
	conf.values.xs = m_IntervalVec.data();
	conf.values.count = static_cast<int>(m_TimingVec.size());
	conf.values.ys = m_TimingVec.data();
	conf.values.color = ImColor(255, 0, 0);
	conf.scale.min = 0;
	conf.scale.max = m_TimingVec[0];
	conf.grid_y.show = true;
	conf.grid_y.size = m_TimingVec[0] / 5;
	conf.tooltip.format = "x=%g, y=%g";
	conf.tooltip.show = true;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(200, 100);
	ImGui::Plot("plot1", conf);

	ImGui::EndChild();
}

amu::TrashTheCacheEx1::TrashTheCacheEx1(GameObject* ownerObjectPtr)
	: Component(ownerObjectPtr)
{

}

void amu::TrashTheCacheEx1::Render() const
{
	if (m_GraphReady)
	{
		DrawPlot();
	}
	ImGui::End();
}

void amu::TrashTheCacheEx1::Update()
{
	ImGui::Begin("Exercise 1");

	ImGui::InputInt("# samples", &m_SampleCount);

	if (!m_Calculating)
	{
		if (ImGui::Button("Trash the cash"))
		{
			m_Promise = std::promise<void>();
			m_Future = m_Promise.get_future();

			std::thread myThread(&TrashTheCacheEx1::TestEx1, this);

			myThread.detach();
			m_Calculating = true;
			m_GraphReady = false;
		}
	}
	else
	{
		ImGui::Text("Wait for it...");
	}
	if (m_Future.valid() && m_Future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
	{
		m_GraphReady = true;
	}
}
