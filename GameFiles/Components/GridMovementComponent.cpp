#include "GridMovementComponent.h"

void pacman::MovementIdle::Update(amu::GameObject*)
{
	std::cout << "Idle\n";
}

void pacman::MovementUp::Update(amu::GameObject*)
{
	std::cout << "Up\n";
}

void pacman::MovementDown::Update(amu::GameObject*)
{
	std::cout << "Down\n";
}

void pacman::MovementLeft::Update(amu::GameObject*)
{
	std::cout << "Left\n";
}

void pacman::MovementRight::Update(amu::GameObject*)
{
	std::cout << "Right\n";
}

pacman::GridMovementComponent::GridMovementComponent(amu::GameObject * gameObjectPtr)
	: amu::Component(gameObjectPtr)
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

