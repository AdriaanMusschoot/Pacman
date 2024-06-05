#ifndef PM_BIG_PICKUP_COLLIDER_H
#define PM_BIG_PICKUP_COLLIDER_H
#include "CollisionComponent.h"
#include "Configuration.h"

namespace pacman
{

	class BigPickupCollider final : public amu::CollisionComponent
	{
	public:
		BigPickupCollider(amu::GameObject* ownerObjectPtr);
		virtual ~BigPickupCollider() override = default;

		BigPickupCollider (BigPickupCollider  const&) = delete;
		BigPickupCollider (BigPickupCollider&&) = delete;
		BigPickupCollider & operator=(BigPickupCollider  const&) = delete;
		BigPickupCollider & operator=(BigPickupCollider&&) = delete;

		void OnCollision(amu::CollisionComponent* otherCollider) override;
	private:
	};

}

#endif //PM_BIG_PICKUP_COLLIDER_H