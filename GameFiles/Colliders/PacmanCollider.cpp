#include "PacmanCollider.h"
#include "Configuration.h"
#include "ServiceLocator.h"
#include "GameTime.h"

pacman::PacmanCollider::PacmanCollider(amu::GameObject* ownerObjectPtr)
	: CollisionComponent(ownerObjectPtr, std::vector<std::string>{ pacman::tags::PICKUP_SMALL, pacman::tags::PICKUP_BIG, pacman::tags::BLINKY })
{
	m_PacmanFSMPtr = GetComponentOwner()->GetComponent<PacmanFSMComponent>();
}

void pacman::PacmanCollider::OnCollision(amu::CollisionComponent* otherCollider)
{
	m_PacmanFSMPtr->HandleOverlap(otherCollider);
}