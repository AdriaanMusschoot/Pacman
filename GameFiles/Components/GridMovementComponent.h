#ifndef PM_GRID_MOVEMENT_COMPONENT_H
#define PM_GRID_MOVEMENT_COMPONENT_H

#include "Component.h"
#include "Configuration.h"
#include "PlayFieldGridComponent.h"
#include "TransformComponent.h"
#include "DistanceComponent.h"

namespace pacman
{

	class GridMovementComponent final : public amu::Component
	{
	public:
		GridMovementComponent(amu::GameObject* gameObjectPtr, PlayFieldGridComponent* playFieldGridPtr, std::int64_t const& speed);
		virtual ~GridMovementComponent() override = default;

		GridMovementComponent(GridMovementComponent const& other) = delete;
		GridMovementComponent(GridMovementComponent&& other) = delete;
		GridMovementComponent& operator=(GridMovementComponent const& other) = delete;
		GridMovementComponent& operator=(GridMovementComponent&& other) = delete;

		void Update() override;
		void ChangeMovementState(glm::vec2 const& newDirection);
	private:
		PlayFieldGridComponent* m_PlayFieldGridPtr{ nullptr };
		amu::TransformComponent* m_TransformPtr{ nullptr };
		pacman::DistanceComponent* m_DistanceComponentPtr{ nullptr };
		glm::vec2 m_CurrentDirection{ 0, 0 };
		glm::vec2 m_NewDirection{ 0, 0 };
		std::int64_t const m_Speed{ 1 };
		PlayFieldGridComponent::Tile m_CurrentTile{};
		bool TileReachable(glm::vec2 const& direction) const;
	};

}

#endif //PM_GRID_MOVEMENT_COMPONENT_H