#include "SmallPickupCollider.h"
#include "GameObject.h"
pacman::SmallPickupCollider::SmallPickupCollider(amu::GameObject* ownerObjectPtr)
	: CollisionComponent(ownerObjectPtr, std::vector<std::string>{})
{
}

void pacman::SmallPickupCollider::OnCollision(amu::CollisionComponent* otherColliderPtr)
{
	if (otherColliderPtr->GetComponentOwner()->GetTag() == tags::PACMAN)
	{
		GetComponentOwner()->EnableToBeDestroyed();
	}
}