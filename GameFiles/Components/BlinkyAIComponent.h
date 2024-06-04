#ifndef PM_BLINKY_AI_COMPONENT
#define PM_BLINKY_AI_COMPONENT

#include "Component.h"
#include "GridMovementComponent.h"
#include "TransformComponent.h"
#include "IObserver.h"
#include "Subject.h"

namespace pacman
{

	class BlinkyAIComponent final : public amu::Component, public amu::IObserver
	{
	public:
		BlinkyAIComponent(amu::GameObject* gameObjectPtr, amu::TransformComponent* pacmanTransformPtr);
		virtual ~BlinkyAIComponent() override = default;

		BlinkyAIComponent(BlinkyAIComponent const&) = delete;
		BlinkyAIComponent(BlinkyAIComponent&&) = delete;
		BlinkyAIComponent& operator=(BlinkyAIComponent const&) = delete;
		BlinkyAIComponent& operator=(BlinkyAIComponent&&) = delete;

		void Notify(Event eventType, amu::Subject* subjectPtr) override;

	private:
		amu::TransformComponent* m_TransformPtr;
		GridMovementComponent* m_GridMovementPtr;
		amu::TransformComponent* m_PacmanTransformPtr;

		glm::vec2 m_PreviousDirection{ 0, 0 };
		
		glm::vec2 GetOptimalDirectionToPacman(std::vector<glm::vec2> const& possibleDirections) const;

		enum class Axis
		{
			X,
			Y
		};

		Axis GetOptimalAxis(float deltaX, float deltaY) const;
		glm::vec2 GetOptimalHorizontalDirection(float deltaX) const;
		glm::vec2 GetOptimalVerticalDirection(float deltaY) const;
	};

}
#endif //PM_BLINKY_AI_COMPONENT