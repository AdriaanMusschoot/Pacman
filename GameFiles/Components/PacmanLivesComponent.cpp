#include "PacmanLivesComponent.h"

pacman::PacmanLivesComponent::PacmanLivesComponent(amu::GameObject* ownerObjectPtr)
	: Component(ownerObjectPtr)
{
	m_LivesTextPtr = GetComponentOwner()->GetComponent<amu::TextComponent>();
}

void pacman::PacmanLivesComponent::OnNotify(Event eventType, amu::Subject*)
{
	if (eventType == events::PACMAN_HIT_GHOST)
	{
		--m_Lives;
		m_LivesTextPtr->SetText(std::to_string(m_Lives));
	}
}