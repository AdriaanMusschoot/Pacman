#ifndef PM_GHOST_FSM_COMPONENT_H
#define PM_GHOST_FSM_COMPONENT_H

#include "Component.h"
#include "GridMovementComponent.h"

namespace pacman
{

	class GhostFSMComponent;

	class BaseGhostState
	{
	public:
		BaseGhostState() = default;
		virtual ~BaseGhostState() = default;

		virtual void OnEnter(GhostFSMComponent* ownerPtr) = 0;
		virtual void OnExit(GhostFSMComponent* ownerPtr) = 0;

		virtual void HandleInput(glm::vec2 const& direction, GhostFSMComponent* ownerPtr) = 0;
		virtual BaseGhostState* Update(double elapsedSec, GhostFSMComponent* ownerPtr) = 0;

		virtual BaseGhostState* HandleOverlap(amu::CollisionComponent* otherColliderPtr, GhostFSMComponent* ownerPtr) = 0;
		virtual BaseGhostState* OnNotify(amu::IObserver::Event eventType, amu::Subject* subjectPtr, GhostFSMComponent* ownerPtr) = 0;

	private:
	};

	class HuntingPacmanState final : public BaseGhostState
	{
	public:
		HuntingPacmanState() = default;
		virtual ~HuntingPacmanState() = default;

		virtual void OnEnter(GhostFSMComponent* ownerPtr) override;
		virtual void OnExit(GhostFSMComponent* ownerPtr) override;

		virtual void HandleInput(glm::vec2 const& direction, GhostFSMComponent* ownerPtr) override;
		virtual BaseGhostState* Update(double elapsedSec, GhostFSMComponent* ownerPtr) override;

		virtual BaseGhostState* HandleOverlap(amu::CollisionComponent* otherColliderPtr, GhostFSMComponent* ownerPtr) override;
		virtual BaseGhostState* OnNotify(amu::IObserver::Event eventType, amu::Subject* subjectPtr, GhostFSMComponent* ownerPtr) override;
	private:
	};

	class GhostFSMComponent final : public amu::Component
	{
	public:
		GhostFSMComponent(amu::GameObject* ownerObjectPtr);
		virtual ~GhostFSMComponent() = default;

		GhostFSMComponent(GhostFSMComponent const&) = delete;
		GhostFSMComponent(GhostFSMComponent&&) = delete;
		GhostFSMComponent& operator=(GhostFSMComponent const&) = delete;
		GhostFSMComponent& operator=(GhostFSMComponent&&) = delete;

	private:
		GridMovementComponent* m_GrideMovement{ nullptr };
	};

}

#endif //PM_GHOST_FSM_COMPONENT_H