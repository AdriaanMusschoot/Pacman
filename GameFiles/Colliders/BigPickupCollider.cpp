#include "BigPickupCollider.h"
#include "GameObject.h"

pacman::BigPickupCollider::BigPickupCollider(amu::GameObject* ownerObjectPtr)
	: CollisionComponent(ownerObjectPtr, std::vector<std::string>{})
	, Subject(ownerObjectPtr)
{
}

void pacman::BigPickupCollider::OnCollision(amu::CollisionComponent* otherCollider)
{
	if (otherCollider->GetComponentOwner()->GetTag() == tags::PACMAN)
	{
		NotifyObservers(events::BIG_PICKUP_VANISHED);
		GetComponentOwner()->EnableToBeDestroyed();
	}
}
