#include "GridMovementComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "GameTime.h"
void pacman::MovementIdle::Update(amu::GameObject*)
{
	std::cout << "Idle\n";
}

void pacman::MovementUp::Update(amu::GameObject* gameObjectPtr)
{
	if (not m_TransformPtr)
	{
		m_TransformPtr = gameObjectPtr->GetComponent<amu::TransformComponent>();
	}
	m_TransformPtr->SetLocalPosition(m_TransformPtr->GetLocalPosition() + glm::vec2{ 0, -10 * amu::GameTime::GetInstance().GetDeltaTime() });
	std::cout << "Up\n";
}

void pacman::MovementDown::Update(amu::GameObject* gameObjectPtr)
{
	if (not m_TransformPtr)
	{
		m_TransformPtr = gameObjectPtr->GetComponent<amu::TransformComponent>();
	}
	m_TransformPtr->SetLocalPosition(m_TransformPtr->GetLocalPosition() + glm::vec2{ 0, 10 * amu::GameTime::GetInstance().GetDeltaTime() });
	std::cout << "Down\n";
}

void pacman::MovementLeft::Update(amu::GameObject* gameObjectPtr)
{
	if (not m_TransformPtr)
	{
		m_TransformPtr = gameObjectPtr->GetComponent<amu::TransformComponent>();
	}
	m_TransformPtr->SetLocalPosition(m_TransformPtr->GetLocalPosition() + glm::vec2{ -10 * amu::GameTime::GetInstance().GetDeltaTime(), 0 });
	std::cout << "Left\n";
}

void pacman::MovementRight::Update(amu::GameObject* gameObjectPtr)
{
	if (not m_TransformPtr)
	{
		m_TransformPtr = gameObjectPtr->GetComponent<amu::TransformComponent>();
	}
	m_TransformPtr->SetLocalPosition(m_TransformPtr->GetLocalPosition() + glm::vec2{ 10 * amu::GameTime::GetInstance().GetDeltaTime(), 0 });
	std::cout << "Right\n";
}

pacman::GridMovementComponent::GridMovementComponent(amu::GameObject * gameObjectPtr, PlayFieldGridComponent* playFieldGridPtr)
	: amu::Component(gameObjectPtr)
	, m_PlayFieldGridPtr{ playFieldGridPtr }
{
}

void pacman::GridMovementComponent::Update()
{
	m_CurrentMovementStateSPtr->Update(GetComponentOwner());
}

void pacman::GridMovementComponent::ChangeMovementState(std::shared_ptr<IMovementState> newStateSPtr)
{
	m_CurrentMovementStateSPtr = newStateSPtr;
}