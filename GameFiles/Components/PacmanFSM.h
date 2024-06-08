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

		virtual std::unique_ptr<BaseStatePickupOverlap> Update(double elapsedSec) = 0;
		virtual std::unique_ptr<BaseStatePickupOverlap> HandleOverlap() = 0;
	private:
	};

	class WaitingStateSmallPickupOverlap final : public BaseStatePickupOverlap
	{
	public:
		WaitingStateSmallPickupOverlap() = default;
		~WaitingStateSmallPickupOverlap() = default;

		void OnExit() override {}
		void OnEnter() override {}

		std::unique_ptr<BaseStatePickupOverlap> Update(double elapsedSec) override;
		std::unique_ptr<BaseStatePickupOverlap> HandleOverlap() override;;
	private:
	};

	class HasEatenStateSmallPickupOverlap final : public BaseStatePickupOverlap
	{
	public:
		HasEatenStateSmallPickupOverlap() = default;
		~HasEatenStateSmallPickupOverlap() = default;

		void OnEnter() override;
		void OnExit() override;

		std::unique_ptr<BaseStatePickupOverlap> Update(double elapsedSec) override;
		std::unique_ptr<BaseStatePickupOverlap> HandleOverlap() override;;
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
		BaseStatePacman* Update(double, PacmanFSMComponent*) override;

		BaseStatePacman* HandleOverlap(amu::CollisionComponent* otherColliderPtr, PacmanFSMComponent* ownerPtr) override;
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
		BaseStatePacman* Update(double, PacmanFSMComponent*) override;

		BaseStatePacman* HandleOverlap(amu::CollisionComponent* otherColliderPtr, PacmanFSMComponent* ownerPtr) override;
	private:
	};

	class PacmanFSMComponent final : public amu::Component, public amu::Subject
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

		template<typename T>
		T* GetState()
		{
			for (const auto& state : m_PMStatesUPtr)
			{
				if (auto const& neededState = dynamic_cast<T*>(state.get()); neededState != nullptr)
				{
					return neededState;
				}
			}
			return nullptr;
		}

		GridMovementComponent* GetGridMove();
	private:
		GridMovementComponent* m_GridMoveCompPtr{ nullptr };

		std::vector<std::unique_ptr<BaseStatePacman>> m_PMStatesUPtr{};

		BaseStatePacman* m_CurrentStatePtr{ nullptr };

		std::unique_ptr<BaseStatePickupOverlap> m_StatePickupUPtr{};
	};

}

#endif //PM_PACMAN_FSM_H