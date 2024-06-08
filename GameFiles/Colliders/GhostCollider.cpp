#include "GhostCollider.h"
#include "GameObject.h"

pacman::GhostCollider::GhostCollider(amu::GameObject* ownerObjectPtr)
	: CollisionComponent(ownerObjectPtr, std::vector<std::string>{})
{
	m_GhostFSMPtr = GetComponentOwner()->GetComponent<GhostFSMComponent>();
	assert(m_GhostFSMPtr);
}

void pacman::GhostCollider::OnCollision(amu::CollisionComponent* otherCollider)
{
	m_GhostFSMPtr->HandleOverlap(otherCollider);
}
