#ifndef PM_BLINKY_AI_COMPONENT
#define PM_BLINKY_AI_COMPONENT

#include "Component.h"
#include "GridMovementComponent.h"
#include "TransformComponent.h"
#include "IObserver.h"
#include "Subject.h"

namespace pacman
{
	class BaseAIComponent : public amu::Component
	{
	public:
		enum class Axis
		{
			X,
			Y
		};
		BaseAIComponent(amu::GameObject* gameObjectPtr);
		virtual ~BaseAIComponent() override = default;

		BaseAIComponent(BaseAIComponent const&) = delete;
		BaseAIComponent(BaseAIComponent&&) = delete;
		BaseAIComponent& operator=(BaseAIComponent const&) = delete;
		BaseAIComponent& operator=(BaseAIComponent&&) = delete;

		virtual glm::vec2 const& GetOptimalDirectionToPacman(std::vector<glm::vec2> const& possibleDirections, glm::vec2 const& pacmanPos, glm::vec2 const& ghostPos, glm::vec2 const& previousDirection) = 0;
		virtual glm::vec2 const& GetOptimalDirectionFromPacman(std::vector<glm::vec2> const& possibleDirections, glm::vec2 const& pacmanPos, glm::vec2 const& ghostPos, glm::vec2 const& previousDirection) = 0;

		Axis GetOptimalAxis(float deltaX, float deltaY) const;
		glm::vec2 GetOptimalHorizontalDirection(float deltaX) const;
		glm::vec2 GetOptimalVerticalDirection(float deltaY) const;
	protected:
		std::vector<glm::vec2> m_PreferredDirectionVec{ 4 };
	};



	class BlinkyAIComponent final : public BaseAIComponent
	{
	public:
		BlinkyAIComponent(amu::GameObject* gameObjectPtr);
		virtual ~BlinkyAIComponent() override = default;

		BlinkyAIComponent(BlinkyAIComponent const&) = delete;
		BlinkyAIComponent(BlinkyAIComponent&&) = delete;
		BlinkyAIComponent& operator=(BlinkyAIComponent const&) = delete;
		BlinkyAIComponent& operator=(BlinkyAIComponent&&) = delete;

		glm::vec2 const& GetOptimalDirectionToPacman(std::vector<glm::vec2> const& possibleDirections, glm::vec2 const& pacmanPos, glm::vec2 const& ghostPos, glm::vec2 const& previousDirection) override;
		glm::vec2 const& GetOptimalDirectionFromPacman(std::vector<glm::vec2> const& possibleDirections, glm::vec2 const& pacmanPos, glm::vec2 const& ghostPos, glm::vec2 const& previousDirection) override;
	private:

	};

}
#endif //PM_BLINKY_AI_COMPONENT