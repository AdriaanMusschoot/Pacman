#ifndef PM_BLINKY_AI_COMPONENT
#define PM_BLINKY_AI_COMPONENT

#include "Component.h"
#include "GridMovementComponent.h"
#include "TransformComponent.h"
#include "IObserver.h"

namespace pacman
{

	class BlinkyAIComponent final : public amu::Component
	{
	public:
		BlinkyAIComponent(amu::GameObject* gameObjectPtr, amu::TransformComponent* pacmanTransformPtr);
		virtual ~BlinkyAIComponent() override = default;

		BlinkyAIComponent(BlinkyAIComponent const&) = delete;
		BlinkyAIComponent(BlinkyAIComponent&&) = delete;
		BlinkyAIComponent& operator=(BlinkyAIComponent const&) = delete;
		BlinkyAIComponent& operator=(BlinkyAIComponent&&) = delete;

		void Update() override;
	private:
		amu::TransformComponent* m_TransformPtr;
		GridMovementComponent* m_GridMovementPtr;
		amu::TransformComponent* m_PacmanTransformPtr;

		bool m_DecisionQueued{ false };
		glm::vec2 FindPacman();
	};

}
#endif //PM_BLINKY_AI_COMPONENT