#pragma once
#include <memory>
#include <string>

#include "Header/Component.h"

namespace dae
{

	class FPSComponent final : public Component
	{
	public:
		FPSComponent(const std::weak_ptr<dae::GameObject>& gameObject);
		~FPSComponent() override = default;
	
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;
	
		void Update() override;
	private:
		std::weak_ptr<dae::GameObject> m_GameObject;
		std::string m_FPSCountToDisplay;
	
		int m_TicksPassed{ 0 };
	
		const double m_MaxRefreshTime{ 0.2 };
		double m_CurrentRefreshTime{ 0.0 };
	};
}