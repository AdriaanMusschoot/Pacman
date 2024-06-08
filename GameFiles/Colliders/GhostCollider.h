#ifndef PM_GHOST_COLLIDER_H
#define PM_GHOST_COLLIDER_H
#include "CollisionComponent.h"
#include "Configuration.h"
#include "Components/GhostFSM.h"

namespace pacman
{

	class GhostCollider final : public amu::CollisionComponent
	{
	public:
		GhostCollider(amu::GameObject* ownerObjectPtr);
		virtual ~GhostCollider() override = default;

		GhostCollider(GhostCollider const&) = delete;
		GhostCollider(GhostCollider&&) = delete;
		GhostCollider& operator=(GhostCollider const&) = delete;
		GhostCollider& operator=(GhostCollider&&) = delete;

		void OnCollision(amu::CollisionComponent* otherCollider) override;
	private:
		GhostFSMComponent* m_GhostFSMPtr{ nullptr };

	};

}

#endif //PM_GHOST_COLLIDER_H