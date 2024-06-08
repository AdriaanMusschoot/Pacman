#include "GhostFSM.h"

pacman::GhostFSMComponent::GhostFSMComponent(amu::GameObject* ownerObjectPtr)
	: Component(ownerObjectPtr)
{
}

void pacman::HuntingPacmanState::OnEnter(GhostFSMComponent*)
{
}

void pacman::HuntingPacmanState::OnExit(GhostFSMComponent*)
{
}

void pacman::HuntingPacmanState::HandleInput(glm::vec2 const&, GhostFSMComponent*)
{
}

pacman::BaseGhostState* pacman::HuntingPacmanState::Update(double, GhostFSMComponent*)
{
	return nullptr;
}

pacman::BaseGhostState* pacman::HuntingPacmanState::HandleOverlap(amu::CollisionComponent*, GhostFSMComponent*)
{
	return nullptr;
}

pacman::BaseGhostState* pacman::HuntingPacmanState::OnNotify(amu::IObserver::Event, amu::Subject*, GhostFSMComponent*)
{
	return nullptr;
}
