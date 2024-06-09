#ifndef PM_BLINKY_AI_COMPONENT
#define PM_BLINKY_AI_COMPONENT

#include "Component.h"
#include "GridMovementComponent.h"
#include "TransformComponent.h"
#include "IObserver.h"
#include "Subject.h"

namespace pacman
{
	class GhostFSMComponent;

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

		virtual glm::vec2 const& GetOptimalDirectionToPacman(std::vector<glm::vec2> const& possibleDirections, GhostFSMComponent* fsmPtr) = 0;
		virtual glm::vec2 const& GetOptimalDirectionFromPacman(std::vector<glm::vec2> const& possibleDirections, GhostFSMComponent* fsmPtr) = 0;

		glm::vec2 const& GetOptimalDirectionToSpawn(std::vector<glm::vec2> const& possibleDirections, GhostFSMComponent* fsmPtr);

		bool IsAtSpawnPos(glm::vec2 const& ghostPos);

	protected:
		Axis GetOptimalAxis(float deltaX, float deltaY) const;
		glm::vec2 GetOptimalHorizontalDirection(float deltaX) const;
		glm::vec2 GetOptimalVerticalDirection(float deltaY) const;

		std::vector<glm::vec2> m_PreferredDirectionVec{ 4 };
	private:
		glm::vec2 m_SpawnPos{ };
		amu::DistanceComponent* m_DistancePtr{ nullptr };
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

		glm::vec2 const& GetOptimalDirectionToPacman(std::vector<glm::vec2> const& possibleDirections, GhostFSMComponent* fsmPtr) override;
		glm::vec2 const& GetOptimalDirectionFromPacman(std::vector<glm::vec2> const& possibleDirections, GhostFSMComponent* fsmPtr) override;
	private:

	};

	class InkyPinkyAIComponent final : public BaseAIComponent
	{
	public:
		InkyPinkyAIComponent(amu::GameObject* gameObjectPtr, float distanceToCheck);
		virtual ~InkyPinkyAIComponent() override = default;

		InkyPinkyAIComponent(InkyPinkyAIComponent const&) = delete;
		InkyPinkyAIComponent(InkyPinkyAIComponent&&) = delete;
		InkyPinkyAIComponent& operator=(InkyPinkyAIComponent const&) = delete;
		InkyPinkyAIComponent& operator=(InkyPinkyAIComponent&&) = delete;

		glm::vec2 const& GetOptimalDirectionToPacman(std::vector<glm::vec2> const& possibleDirections, GhostFSMComponent* fsmPtr) override;
		glm::vec2 const& GetOptimalDirectionFromPacman(std::vector<glm::vec2> const& possibleDirections, GhostFSMComponent* fsmPtr) override;
	private:
		float m_DistanceToCheck{};
	};

	class ClydeAIComponent final : public BaseAIComponent
	{
	public:
		ClydeAIComponent(amu::GameObject* gameObjectPtr);
		virtual ~ClydeAIComponent() override = default;

		ClydeAIComponent(ClydeAIComponent const&) = delete;
		ClydeAIComponent(ClydeAIComponent&&) = delete;
		ClydeAIComponent& operator=(ClydeAIComponent const&) = delete;
		ClydeAIComponent& operator=(ClydeAIComponent&&) = delete;

		glm::vec2 const& GetOptimalDirectionToPacman(std::vector<glm::vec2> const& possibleDirections, GhostFSMComponent* fsmPtr) override;
		glm::vec2 const& GetOptimalDirectionFromPacman(std::vector<glm::vec2> const& possibleDirections, GhostFSMComponent* fsmPtr) override;
	private:
	};

}
#endif //PM_BLINKY_AI_COMPONENT