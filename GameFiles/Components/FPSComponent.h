#ifndef PM_FPS_COMPONENT_H
#define PM_FPS_COMPONENT_H
#include <string>

#include "Component.h"
#include "TextComponent.h"

namespace pacman
{

	class FPSComponent final : public amu::Component
	{
	public:
		FPSComponent(amu::GameObject * ownerObjectPtr);
		virtual ~FPSComponent() override = default;
	
		FPSComponent(FPSComponent const&) = delete;
		FPSComponent(FPSComponent&&) = delete;
		FPSComponent& operator=(FPSComponent const&) = delete;
		FPSComponent& operator=(FPSComponent&&) = delete;
	
		void Update() override;
	private:
		amu::TextComponent* m_TextPtr{ nullptr };

		std::string m_FPSCountToDisplay{ "" };
	
		int m_TicksPassed{ 0 };
	
		const double m_MaxRefreshTime{ 0.2 };
		double m_CurrentRefreshTime{ 0.0 };

		double m_PreviousFPSCount{ 0 };

	};
}

#endif //PM_FPS_COMPONENT_H