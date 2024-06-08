#include "GhostCollider.h"
#include "GameObject.h"

pacman::GhostCollider::GhostCollider(amu::GameObject* ownerObjectPtr)
	: CollisionComponent(ownerObjectPtr, std::vector<std::string>{})
{
}

void pacman::GhostCollider::OnCollision(amu::CollisionComponent* otherCollider)
{
	if (otherCollider->GetComponentOwner()->GetTag() == tags::PACMAN)
	{
		std::cout << "Colliding w/ pacman\n";
	}
}
