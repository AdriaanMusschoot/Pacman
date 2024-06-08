#ifndef PM_SMALL_PICKUP_COLLIDER_H
#define PM_SMALL_PICKUP_COLLIDER_H
#include "CollisionComponent.h"
#include "Configuration.h"
#include "Subject.h"

namespace pacman
{

	class SmallPickupCollider final : public amu::CollisionComponent, public amu::Subject
	{
	public:
		SmallPickupCollider(amu::GameObject* ownerObjectPtr);
		virtual ~SmallPickupCollider() override = default;

		SmallPickupCollider(SmallPickupCollider const&) = delete;
		SmallPickupCollider(SmallPickupCollider&&) = delete;
		SmallPickupCollider& operator=(SmallPickupCollider const&) = delete;
		SmallPickupCollider& operator=(SmallPickupCollider&&) = delete;

		void OnCollision(amu::CollisionComponent* otherCollider) override;
	private:
	};

}

#endif //PM_SMALL_PICKUP_COLLIDER_H