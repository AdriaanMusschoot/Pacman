#ifndef PM_SMALL_PICKUP_COLLIDER_H
#define PM_SMALL_PICKUP_COLLIDER_H
#include "CollisionComponent.h"

namespace pacman
{

	class SmallPickupCollider final : public amu::CollisionComponent
	{
	public:
		SmallPickupCollider(amu::GameObject* ownerObjectPtr);
		virtual ~SmallPickupCollider() override = default;

		SmallPickupCollider(SmallPickupCollider const& other) = delete;
		SmallPickupCollider(SmallPickupCollider&& other) = delete;
		SmallPickupCollider& operator=(SmallPickupCollider const& other) = delete;
		SmallPickupCollider& operator=(SmallPickupCollider&& other) = delete;

		void OnCollision(amu::CollisionComponent* otherCollider) override;
	private:
	};

}

#endif //PM_SMALL_PICKUP_COLLIDER_H