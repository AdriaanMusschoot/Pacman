#include "ScoreComponent.h"
#include "Observer.h"

amu::ScoreComponent::ScoreComponent(GameObject* ownerObjectPtr, int score)
	: Component(ownerObjectPtr)
	, Subject(ownerObjectPtr)
	, m_CurrentScore{ score }
{
}

void amu::ScoreComponent::IncreaseScore(int value)
{
	m_CurrentScore += value;
	NotifyObservers(Observer::EventType::PacmanEat);
}

int amu::ScoreComponent::GetScore() const
{
	return m_CurrentScore;
}
