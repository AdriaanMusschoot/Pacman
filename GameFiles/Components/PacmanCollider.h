#ifndef PM_PACMAN_COLLIDER_H
#define PM_PACMAN_COLLIDER_H
#include "CollisionComponent.h"

namespace pacman
{

	class PacmanCollider final : public amu::CollisionComponent
	{
	public:
		PacmanCollider(amu::GameObject* ownerObjectPtr);
		virtual ~PacmanCollider() override = default;

		PacmanCollider(PacmanCollider const& other) = delete;
		PacmanCollider(PacmanCollider&& other) = delete;
		PacmanCollider& operator=(PacmanCollider const& other) = delete;
		PacmanCollider& operator=(PacmanCollider&& other) = delete;

		void OnCollision(amu::CollisionComponent* otherCollider) override;
	private:
	};

}

#endif //PM_PACMAN_COLLIDER_H