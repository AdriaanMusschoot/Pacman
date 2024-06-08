#ifndef PM_PACMAN_LIVES_COMPONENT_H
#define PM_PACMAN_LIVES_COMPONENT_H

#include "Component.h"
#include "Configuration.h"
#include "TextComponent.h"
#include "IObserver.h"
#include "GameObject.h"

namespace pacman
{

	class PacmanLivesComponent final : public amu::Component, public amu::IObserver
	{
	public:
		PacmanLivesComponent(amu::GameObject* ownerObjectPtr);
		virtual ~PacmanLivesComponent() override = default;

		PacmanLivesComponent(PacmanLivesComponent const&) = delete;
		PacmanLivesComponent(PacmanLivesComponent&&) = delete;
		PacmanLivesComponent& operator=(PacmanLivesComponent const&) = delete;
		PacmanLivesComponent& operator=(PacmanLivesComponent&&) = delete;

		void OnNotify(Event eventType, amu::Subject* subjectPtr) override;
	private:
		amu::TextComponent* m_LivesTextPtr{ nullptr };
		int m_Lives{ 3 };
	};

}

#endif //PM_PACMAN_LIVES_COMPONENT_H