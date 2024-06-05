#ifndef PM_GRID_MOVEMENT_COMPONENT_H
#define PM_GRID_MOVEMENT_COMPONENT_H

#include "Component.h"
#include "Configuration.h"
#include "PlayFieldGridComponent.h"
#include "TransformComponent.h"
#include "DistanceComponent.h"
#include "Subject.h"

namespace pacman
{

	class GridMovementComponent final : public amu::Component, public amu::Subject
	{
	public:
		GridMovementComponent(amu::GameObject* gameObjectPtr, PlayFieldGridComponent* playFieldGridPtr, std::int64_t const& speed);
		virtual ~GridMovementComponent() override = default;

		GridMovementComponent(GridMovementComponent const&) = delete;
		GridMovementComponent(GridMovementComponent&&) = delete;
		GridMovementComponent& operator=(GridMovementComponent const&) = delete;
		GridMovementComponent& operator=(GridMovementComponent&&) = delete;

		void Update() override;
		void ChangeMovementState(glm::vec2 const& newDirection);
		std::vector<glm::vec2> PossibleDirections();
		glm::vec2 const& GetCurrentDirection() const;
	private:
		PlayFieldGridComponent* m_PlayFieldGridPtr{ nullptr };
		amu::TransformComponent* m_TransformPtr{ nullptr };
		glm::vec2 m_CurrentDirection{ 0, 0 };
		glm::vec2 m_NewDirection{ 0, 0 };
		glm::vec2 m_OldPosition{ 0, 0 };
		glm::vec2 m_PredictedPosition{ 0, 0 };
		std::int64_t const m_Speed{ 1 };
		PlayFieldGridComponent::Tile m_CurrentTile{};
		std::string const m_Tag{};
		bool TileReachable(glm::vec2 const& direction) const;
		bool IsCentered() const;
	};

}

#endif //PM_GRID_MOVEMENT_COMPONENT_H