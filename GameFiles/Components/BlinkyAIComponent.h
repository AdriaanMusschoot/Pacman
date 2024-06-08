#ifndef PM_BLINKY_AI_COMPONENT
#define PM_BLINKY_AI_COMPONENT

#include "Component.h"
#include "GridMovementComponent.h"
#include "TransformComponent.h"
#include "IObserver.h"
#include "Subject.h"

namespace pacman
{

	class BlinkyAIComponent;

	class BaseGhostState
	{
	public:
		enum class Axis
		{
			X,
			Y
		};

		BaseGhostState() = default;
		virtual ~BaseGhostState() = default;

		virtual void OnEnter(BlinkyAIComponent* ownerPtr) = 0;
		virtual void OnExit(BlinkyAIComponent* ownerPtr) = 0;

		virtual BaseGhostState* Update(BlinkyAIComponent* ownerPtr, double elapsedSec) = 0;
		virtual BaseGhostState* HandleOverlap(BlinkyAIComponent* ownerPtr, amu::CollisionComponent* otherColliderPtr) = 0;
		virtual BaseGhostState* HandleEvent(BlinkyAIComponent* ownerPtr, amu::IObserver::Event eventType, amu::Subject* subjectPtr) = 0;

		virtual glm::vec2 const& GetOptimalDirection(BlinkyAIComponent* ownerPtr, std::vector<glm::vec2> const& possibleDirections) = 0;
		Axis GetOptimalAxis(float deltaX, float deltaY) const;
		glm::vec2 GetOptimalHorizontalDirection(float deltaX) const;
		glm::vec2 GetOptimalVerticalDirection(float deltaY) const;
	protected:
		std::vector<glm::vec2> m_PreferredDirectionVec{ 4 };
	};

	class HuntPacmanState final : public BaseGhostState
	{
	public: 
		HuntPacmanState() = default;
		virtual ~HuntPacmanState() = default;

		void OnEnter(BlinkyAIComponent*) override {};
		void OnExit(BlinkyAIComponent*) override {};

		virtual BaseGhostState* Update(BlinkyAIComponent*, double) override;
		virtual BaseGhostState* HandleOverlap(BlinkyAIComponent*, amu::CollisionComponent*) override;
		virtual BaseGhostState* HandleEvent(BlinkyAIComponent* ownerPtr, amu::IObserver::Event eventType, amu::Subject* subjectPtr) override;

		glm::vec2 const& GetOptimalDirection(BlinkyAIComponent* ownerPtr, std::vector<glm::vec2> const& possibleDirections) override;
	private:
	};

	class AvoidPacmanState final : public BaseGhostState
	{
	public:
		AvoidPacmanState() = default;
		virtual ~AvoidPacmanState() = default;

		void OnEnter(BlinkyAIComponent* ownerPtr) override;
		void OnExit(BlinkyAIComponent* ownerPtr) override;

		virtual BaseGhostState* Update(BlinkyAIComponent* ownerPtr, double elapsedSec);
		virtual BaseGhostState* HandleOverlap(BlinkyAIComponent*, amu::CollisionComponent*) override;
		virtual BaseGhostState* HandleEvent(BlinkyAIComponent*, amu::IObserver::Event, amu::Subject*) override;

		glm::vec2 const& GetOptimalDirection(BlinkyAIComponent* ownerPtr, std::vector<glm::vec2> const& possibleDirections) override;
	private:
		double m_Timer{ 0.0 };
		double m_MaxTime{ 10 };
	};

	class BlinkyAIComponent final : public amu::Component, public amu::IObserver, public amu::Subject
	{
	public:

		BlinkyAIComponent(amu::GameObject* gameObjectPtr, amu::TransformComponent* pacmanTransformPtr);
		virtual ~BlinkyAIComponent() override = default;

		BlinkyAIComponent(BlinkyAIComponent const&) = delete;
		BlinkyAIComponent(BlinkyAIComponent&&) = delete;
		BlinkyAIComponent& operator=(BlinkyAIComponent const&) = delete;
		BlinkyAIComponent& operator=(BlinkyAIComponent&&) = delete;

		void Update() override;

		void OnNotify(Event eventType, amu::Subject* subjectPtr) override;

		glm::vec2 const& GetPreviousDirection();
		glm::vec2 const& GetPacmanPosition();
		glm::vec2 const& GetGhostPosition();

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

		GridMovementComponent* GetGridMoveComp() const;
	private:
		amu::TransformComponent* m_TransformPtr{ nullptr };
		GridMovementComponent* m_GridMovementPtr{ nullptr };
		amu::TransformComponent* m_PacmanTransformPtr{ nullptr };

		glm::vec2 m_PreviousDirection{ 0, 0 };

		std::vector<std::unique_ptr<BaseGhostState>> m_GhostStateUPtrVec{};

		BaseGhostState* m_CurrentStatePtr{ nullptr };
	};

}
#endif //PM_BLINKY_AI_COMPONENT