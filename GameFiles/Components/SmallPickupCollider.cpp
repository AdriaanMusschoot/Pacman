#include "SmallPickupCollider.h"
#include "GameObject.h"
pacman::SmallPickupCollider::SmallPickupCollider(amu::GameObject* ownerObjectPtr)
	: CollisionComponent(ownerObjectPtr, std::vector<std::string>{ "Pacman" })
{
}

void pacman::SmallPickupCollider::OnCollision(amu::CollisionComponent*)
{
	GetComponentOwner()->EnableToBeDestroyed();
}
