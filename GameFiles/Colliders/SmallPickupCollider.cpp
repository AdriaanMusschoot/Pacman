#include "SmallPickupCollider.h"
#include "GameObject.h"
pacman::SmallPickupCollider::SmallPickupCollider(amu::GameObject* ownerObjectPtr)
	: CollisionComponent(ownerObjectPtr, std::vector<std::string>{})
	, Subject(ownerObjectPtr)
{
}

void pacman::SmallPickupCollider::OnCollision(amu::CollisionComponent* otherColliderPtr)
{
	if (otherColliderPtr->GetComponentOwner()->GetTag() == tags::PACMAN)
	{
		NotifyObservers(events::SMALL_PICKUP_VANISHED);
		GetComponentOwner()->EnableToBeDestroyed();
	}
}
