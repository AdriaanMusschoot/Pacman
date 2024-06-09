#ifndef PM_PACMAN_FSM_H
#define PM_PACMAN_FSM_H
#include "Component.h"
#include "GameObject.h"
#include "GridMovementComponent.h"

namespace pacman
{
	class PacmanFSMComponent;

	class BaseStatePickupOverlap
	{
	public:
		BaseStatePickupOverlap() = default;
		virtual ~BaseStatePickupOverlap() = default;

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;

		virtual BaseStatePickupOverlap* Update(double elapsedSec, PacmanFSMComponent* ownerPtr) = 0;
		virtual BaseStatePickupOverlap* HandleOverlap(amu::CollisionComponent* otherColliderPtr, PacmanFSMComponent* ownerPtr) = 0;
	private:
	};

	class WaitingStateSmallPickupOverlap final : public BaseStatePickupOverlap
	{
	public:
		WaitingStateSmallPickupOverlap() = default;
		~WaitingStateSmallPickupOverlap() = default;

		void OnExit() override {}
		void OnEnter() override {}

		BaseStatePickupOverlap* Update(double elapsedSec, PacmanFSMComponent* ownerPtr) override;
		BaseStatePickupOverlap* HandleOverlap(amu::CollisionComponent* otherColliderPtr, PacmanFSMComponent* ownerPtr) override;
	private:
	};

	class HasEatenStateSmallPickupOverlap final : public BaseStatePickupOverlap
	{
	public:
		HasEatenStateSmallPickupOverlap() = default;
		~HasEatenStateSmallPickupOverlap() = default;

		void OnEnter() override;
		void OnExit() override;

		BaseStatePickupOverlap* Update(double elapsedSec, PacmanFSMComponent* ownerPtr) override;
		BaseStatePickupOverlap* HandleOverlap(amu::CollisionComponent* otherColliderPtr, PacmanFSMComponent* ownerPtr) override;
	private:
		double m_Timer{};
		double m_MaxTime{ 0.3 };
	};

	class BaseStatePacman
	{
	public:
		BaseStatePacman() = default;
		virtual ~BaseStatePacman() = default;

		virtual void OnEnter(PacmanFSMComponent* ownerPtr) = 0;
		virtual void OnExit(PacmanFSMComponent* ownerPtr) = 0;

		virtual void HandleInput(glm::vec2 const& direction, PacmanFSMComponent* ownerPtr) = 0;
		virtual BaseStatePacman* Update(double elapsedSec, PacmanFSMComponent* ownerPtr) = 0;

		virtual BaseStatePacman* HandleOverlap(amu::CollisionComponent* otherColliderPtr, PacmanFSMComponent* ownerPtr) = 0;
		virtual BaseStatePacman* OnNotify(amu::IObserver::Event eventType, amu::Subject* subjectPtr, PacmanFSMComponent* ownerPtr) = 0;
	private:
	};

	class CollectingState final : public BaseStatePacman
	{
	public:
		CollectingState() = default;
		virtual ~CollectingState() = default;

		virtual void OnEnter(PacmanFSMComponent* ownerPtr) override;
		virtual void OnExit(PacmanFSMComponent* ownerPtr) override;

		void HandleInput(glm::vec2 const& direction, PacmanFSMComponent* ownerPtr) override;
		BaseStatePacman* Update(double elapsedSec, PacmanFSMComponent* ownerPtr) override;

		BaseStatePacman* HandleOverlap(amu::CollisionComponent* otherColliderPtr, PacmanFSMComponent* ownerPtr) override;
		BaseStatePacman* OnNotify(amu::IObserver::Event eventType, amu::Subject* subjectPtr, PacmanFSMComponent* ownerPtr) override;
	private:
	};

	class DyingState final : public BaseStatePacman
	{
	public:
		DyingState() = default;
		virtual ~DyingState() = default;

		virtual void OnEnter(PacmanFSMComponent* ownerPtr) override;
		virtual void OnExit(PacmanFSMComponent* ownerPtr) override;

		void HandleInput(glm::vec2 const& direction, PacmanFSMComponent* ownerPtr) override;
		BaseStatePacman* Update(double elapsedSec, PacmanFSMComponent* ownerPtr) override;

		BaseStatePacman* HandleOverlap(amu::CollisionComponent* otherColliderPtr, PacmanFSMComponent* ownerPtr) override;
		BaseStatePacman* OnNotify(amu::IObserver::Event eventType, amu::Subject* subjectPtr, PacmanFSMComponent* ownerPtr) override;
	private:
	};

	class EvilState final : public BaseStatePacman
	{
	public:
		EvilState() = default;
		virtual ~EvilState() = default;

		virtual void OnEnter(PacmanFSMComponent* ownerPtr) override;
		virtual void OnExit(PacmanFSMComponent* ownerPtr) override;

		void HandleInput(glm::vec2 const& direction, PacmanFSMComponent* ownerPtr) override;
		BaseStatePacman* Update(double elapsedSec, PacmanFSMComponent* ownerPtr) override;

		BaseStatePacman* HandleOverlap(amu::CollisionComponent* otherColliderPtr, PacmanFSMComponent* ownerPtr) override;
		BaseStatePacman* OnNotify(amu::IObserver::Event eventType, amu::Subject* subjectPtr, PacmanFSMComponent* ownerPtr) override;
	private:
		double m_Timer{ 0.0 };
		double m_MaxTime{ config::MAX_TIME_PICKUP };
	};

	class PacmanFSMComponent final : public amu::Component, public amu::Subject, public amu::IObserver
	{
	public:
		PacmanFSMComponent(amu::GameObject* ownerObjectPtr);
		virtual ~PacmanFSMComponent() = default;

		PacmanFSMComponent(PacmanFSMComponent const&) = delete;
		PacmanFSMComponent(PacmanFSMComponent&&) = delete;
		PacmanFSMComponent& operator=(PacmanFSMComponent const&) = delete;
		PacmanFSMComponent& operator=(PacmanFSMComponent&&) = delete;

		void HandleInput(glm::vec2 const& direction);

		void HandleOverlap(amu::CollisionComponent* otherColliderPtr);
		void Update() override;

		void OnNotify(Event eventType, amu::Subject* subjectPtr) override;

		template<typename T>
		T* GetState()
		{
			for (auto const& state : m_PMStatesUPtrVec)
			{
				if (auto const& neededState = dynamic_cast<T*>(state.get()); neededState != nullptr)
				{
					return neededState;
				}
			}
			return nullptr;
		}

		template<typename T>
		T* GetPickupState()
		{
			for (auto const& state : m_PickupStatesUPtrVec)
			{
				if (auto const& neededState = dynamic_cast<T*>(state.get()); neededState != nullptr)
				{
					return neededState;
				}
			}
			return nullptr;
		}

		BaseStatePickupOverlap* GetCurrentPickupState();

		void SetCurrentPickupState(BaseStatePickupOverlap* newStatePtr);

		GridMovementComponent* GetGridMove();
	private:
		GridMovementComponent* m_GridMoveCompPtr{ nullptr };

		std::vector<std::unique_ptr<BaseStatePacman>> m_PMStatesUPtrVec{};

		std::vector<std::unique_ptr<BaseStatePickupOverlap>> m_PickupStatesUPtrVec{};

		BaseStatePacman* m_CurrentStatePtr{ nullptr };

		BaseStatePickupOverlap* m_CurrentStatePickupPtr{ nullptr };

		glm::vec2 m_SpawnPos{};
	};

}

#endif //PM_PACMAN_FSM_H