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

		int m_CurrentColIdx{ 0 };

		int const m_ColsPerDirection{ 2 };

		int m_CurrentDirectionIdx{};

		int const m_ColIdxRight{ 0 };
		int const m_ColIdxLeft{ 2 };
		int const m_ColIdxUp{ 4 };
		int const m_ColIdxDown{ 6 };
	};

}

#endif //PM_GHOST_ANIM_COMPONENT_H