#ifndef PM_PACMAN_ANIM_COMPONENT_H
#define PM_PACMAN_ANIM_COMPONENT_H

#include "Component.h"
#include "RenderComponent.h"
#include "IObserver.h"
#include "Configuration.h"
#include "Subject.h"

namespace pacman
{

	class PacmanAnimationComponent final : public amu::Component, public amu::IObserver, public amu::Subject
	{
	public:
		PacmanAnimationComponent(amu::GameObject* ownerObjectPtr);
		virtual ~PacmanAnimationComponent() override = default;

		PacmanAnimationComponent(PacmanAnimationComponent const&) = delete;
		PacmanAnimationComponent(PacmanAnimationComponent&&) = delete;
		PacmanAnimationComponent& operator=(PacmanAnimationComponent const&) = delete;
		PacmanAnimationComponent& operator=(PacmanAnimationComponent&&) = delete;

		void Update() override;
		void OnNotify(Event eventType, amu::Subject* subjectPtr) override;

	private:
		amu::RenderComponent* m_RenderComponentPtr{ nullptr };
		double m_Timer{};
		double m_MaxTime{ 0.1 };

		bool m_Dying{ false };

		bool m_Stuck{ true };

		int m_CurrentRowIdx{ 0 };

		int const m_ColsPerAnimation{ 3 };

		int m_CurrentColIdx{ 2 };

		int const m_RowIdxRight{ 0 };
		int const m_RowIdxLeft{ 1 };
		int const m_RowIdxUp{ 2 };
		int const m_RowIdxDown{ 3 };
	};

}

#endif //PM_PACMAN_ANIM_COMPONENT_H