#ifndef PM_GHOST_ANIM_COMPONENT_H
#define PM_GHOST_ANIM_COMPONENT_H

#include "Component.h"
#include "RenderComponent.h"
#include "IObserver.h"
#include "Configuration.h"
#include "Subject.h"

namespace pacman
{

	class GhostAnimationComponent final : public amu::Component, public amu::IObserver
	{
	public:
		GhostAnimationComponent(amu::GameObject* ownerObjectPtr);
		virtual ~GhostAnimationComponent() override = default;

		GhostAnimationComponent(GhostAnimationComponent  const&) = delete;
		GhostAnimationComponent(GhostAnimationComponent&&) = delete;
		GhostAnimationComponent& operator=(GhostAnimationComponent  const&) = delete;
		GhostAnimationComponent& operator=(GhostAnimationComponent&&) = delete;

		void Update() override;
		void OnNotify(Event eventType, amu::Subject* subjectPtr) override;

	private:
		amu::RenderComponent* m_RenderComponentPtr{ nullptr };
		double m_Timer{};
		double m_MaxTime{ 0.5 };

		double m_TimerFlicker{};
		double m_MaxTimeFlicker{};
		double const m_StartValueFlicker{ config::MAX_TIME_PICKUP / 3.5 + 0.4 };
		double const m_DecreaseValueFlicker{ m_StartValueFlicker / 5 };

		bool m_Afraid{ false };
		bool m_Returning{ false };
		int m_CurrentColIdx{ 0 };

		int const m_ColsPerDirection{ 2 };
		int const m_ColsPerDirectionReturn{ 4 };
		int m_CurrentOffsetIdx{};

		int const m_ColIdxRight{ 0 };
		int const m_ColIdxLeft{ 2 };
		int const m_ColIdxUp{ 4 };
		int const m_ColIdxDown{ 6 };
		int const m_ColAfraid1{ 8 };
		int const m_ColAfraid2{ 10 };
		int const m_ColReturn{ 12 };
	};

}

#endif //PM_GHOST_ANIM_COMPONENT_H