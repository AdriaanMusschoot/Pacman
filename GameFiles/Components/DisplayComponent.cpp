#include "DisplayComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include <format>

amu::DisplayComponent::DisplayComponent(GameObject* gameObjectPtr, const std::string& textToDisplay)
	: Component(gameObjectPtr)
	, m_TextToDisplay{ textToDisplay }
{
	GetComponentOwner()->AddComponent<TextComponent>(GetComponentOwner(), m_TextToDisplay, "Lingua.otf", 20);
	m_TextComponentPtr = GetComponentOwner()->GetComponent<TextComponent>();
}

void amu::DisplayComponent::Notify(EventType eventType, Subject* subjectPtr)
{
	switch (eventType)
	{
	case EventType::PacmanDied:
	{
		int tempHealth{ subjectPtr->GetSubjectOwner()->GetComponent<amu::HealthComponent>()->GetLives() };
		if (m_TextComponentPtr)
		{
			m_TextComponentPtr->SetText(m_TextToDisplay + std::format("{:}", tempHealth));
		}
		break;
	}
	case EventType::PacmanEat:
		int tempScore{ subjectPtr->GetSubjectOwner()->GetComponent<amu::ScoreComponent>()->GetScore() };
		if (m_TextComponentPtr)
		{
			m_TextComponentPtr->SetText(m_TextToDisplay + std::format("{:}", tempScore));
		}
		break;
	}
}

void amu::DisplayComponent::NotifyDestruction()
{
	GetComponentOwner()->EnableToBeDestroyed();
}
