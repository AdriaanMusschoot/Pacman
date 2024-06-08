#ifndef PM_GHOST_FSM_COMPONENT_H
#define PM_GHOST_FSM_COMPONENT_H

#include "Component.h"
#include "GridMovementComponent.h"
#include "GhostAIComponents.h"

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

		void OnEnter(GhostFSMComponent* ownerPtr) override;
		void OnExit(GhostFSMComponent* ownerPtr) override;

		void HandleInput(glm::vec2 const& direction, GhostFSMComponent* ownerPtr) override;
		BaseGhostState* Update(double elapsedSec, GhostFSMComponent* ownerPtr) override;

		BaseGhostState* HandleOverlap(amu::CollisionComponent* otherColliderPtr, GhostFSMComponent* ownerPtr) override;
		BaseGhostState* OnNotify(amu::IObserver::Event eventType, amu::Subject* subjectPtr, GhostFSMComponent* ownerPtr) override;

	private:
	};

	class AvoidingPacmanState final : public BaseGhostState
	{
	public:
		AvoidingPacmanState() = default;
		virtual ~AvoidingPacmanState() = default;

		void OnEnter(GhostFSMComponent* ownerPtr) override;
		void OnExit(GhostFSMComponent* ownerPtr) override;

		void HandleInput(glm::vec2 const& direction, GhostFSMComponent* ownerPtr) override;
		BaseGhostState* Update(double elapsedSec, GhostFSMComponent* ownerPtr) override;

		BaseGhostState* HandleOverlap(amu::CollisionComponent* otherColliderPtr, GhostFSMComponent* ownerPtr) override;
		BaseGhostState* OnNotify(amu::IObserver::Event eventType, amu::Subject* subjectPtr, GhostFSMComponent* ownerPtr) override;

	private:
	};

	class EatenByPacmanState final : public BaseGhostState
	{
	public:
		EatenByPacmanState() = default;
		virtual ~EatenByPacmanState() = default;

		void OnEnter(GhostFSMComponent* ownerPtr) override;
		void OnExit(GhostFSMComponent* ownerPtr) override;

		void HandleInput(glm::vec2 const& direction, GhostFSMComponent* ownerPtr) override;
		BaseGhostState* Update(double elapsedSec, GhostFSMComponent* ownerPtr) override;

		BaseGhostState* HandleOverlap(amu::CollisionComponent* otherColliderPtr, GhostFSMComponent* ownerPtr) override;
		BaseGhostState* OnNotify(amu::IObserver::Event eventType, amu::Subject* subjectPtr, GhostFSMComponent* ownerPtr) override;

	private:
		std::int64_t m_StartSpeed{ };
	};

	class GhostFSMComponent final : public amu::Component, public amu::IObserver, public amu::Subject
	{
	public:
		GhostFSMComponent(amu::GameObject* ownerObjectPtr, amu::GameObject* pacmanPtr);
		virtual ~GhostFSMComponent() = default;

		GhostFSMComponent(GhostFSMComponent const&) = delete;
		GhostFSMComponent(GhostFSMComponent&&) = delete;
		GhostFSMComponent& operator=(GhostFSMComponent const&) = delete;
		GhostFSMComponent& operator=(GhostFSMComponent&&) = delete;

		void HandleInput(glm::vec2 const& direction);

		void HandleOverlap(amu::CollisionComponent* otherColliderPtr);
		void Update() override;

		void OnNotify(amu::IObserver::Event eventType, amu::Subject* subjectPtr) override;

		template <typename T>
		T* GetState()
		{
			for (const auto& state : m_GhostStateUPtrVec)
			{
				if (auto const& neededState = dynamic_cast<T*>(state.get()); neededState != nullptr)
				{
					return neededState;
				}
			}
			return nullptr;
		}

		BaseGhostState* GetGhostState() const;

		void SetPreviousDirection(glm::vec2 const& direction);
		glm::vec2 const& GetPreviousDirection();
		glm::vec2 const& GetPacmanPosition();
		glm::vec2 const& GetPacmanDirection();
		glm::vec2 const& GetGhostPosition();

		GridMovementComponent* GetGridMove() const;
		BaseAIComponent* GetAI() const;
	private:
		GridMovementComponent* m_GridMovementPtr{ nullptr };

		amu::TransformComponent* m_TransformPtr{ nullptr };

		amu::GameObject* m_PacmanPtr{ nullptr };

		std::vector<std::unique_ptr<BaseGhostState>> m_GhostStateUPtrVec{};

		BaseGhostState* m_CurrentGhostStatePtr{ nullptr };

		glm::vec2 m_PreviousDirection{ 0, 0 };

		BaseAIComponent* m_AIPtr{};
	};

}

#endif //PM_GHOST_FSM_COMPONENT_H