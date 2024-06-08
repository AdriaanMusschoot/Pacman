#ifndef PM_PACMAN_COLLIDER_H
#define PM_PACMAN_COLLIDER_H
#include "CollisionComponent.h"
#include "Subject.h"
#include "Components/PacmanFSM.h"
#include <iostream>
namespace pacman
{
	class PacmanCollider final : public amu::CollisionComponent, public amu::Subject
	{
	public:
		PacmanCollider(amu::GameObject* ownerObjectPtr);
		virtual ~PacmanCollider() override = default;

		PacmanCollider(PacmanCollider const&) = delete;
		PacmanCollider(PacmanCollider&&) = delete;
		PacmanCollider& operator=(PacmanCollider const&) = delete;
		PacmanCollider& operator=(PacmanCollider&&) = delete;

		void OnCollision(amu::CollisionComponent* otherCollider) override;
	private:
		PacmanFSMComponent* m_PacmanFSMPtr{ nullptr };
	};

}
 
#endif //PM_PACMAN_COLLIDER_H