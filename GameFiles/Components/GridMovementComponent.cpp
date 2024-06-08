#include "GridMovementComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "GameTime.h"

pacman::GridMovementComponent::GridMovementComponent(amu::GameObject * gameObjectPtr, PlayFieldGridComponent* playFieldGridPtr, std::int64_t const& speed)
	: amu::Component(gameObjectPtr)
	, amu::Subject(gameObjectPtr)
	, m_PlayFieldGridPtr{ playFieldGridPtr }
	, m_TransformPtr{ GetComponentOwner()->GetComponent<amu::TransformComponent>() }
	, m_Speed{ speed }
	, m_CurrentTile{ playFieldGridPtr->GetTile(m_TransformPtr->GetWorldPosition()) }
	, m_Tag{ gameObjectPtr->GetTag() }
{

}

void pacman::GridMovementComponent::Update()
{
	if (not m_TransformPtr)
	{
		return;
	}

	double const& deltaTime = amu::GameTime::GetInstance().GetDeltaTime();
	glm::vec2 offset{ m_CurrentDirection.x * m_Speed * deltaTime, m_CurrentDirection.y * m_Speed * deltaTime };

	m_PredictedPosition = m_TransformPtr->GetLocalPosition() + offset;

	m_CurrentPosition = m_TransformPtr->GetWorldPosition();

	m_CurrentTile = m_PlayFieldGridPtr->GetTile(m_CurrentPosition);

	if (IsCentered())
	{
		m_TransformPtr->SetLocalPosition(m_CurrentTile.Center);
		if (m_Tag == pacman::tags::GHOST and m_CurrentTile.Type == PlayFieldGridComponent::TileType::Crossing)
		{
			NotifyObservers(events::GHOST_INPUT_REQUIRED);
		}
		if ((m_CurrentTile.Type == PlayFieldGridComponent::TileType::Crossing or
			m_CurrentTile.Type == PlayFieldGridComponent::TileType::Pathway) and
			m_NewDirection != config::VEC_NEUTRAL and
			m_CurrentDirection != m_NewDirection and
			TileReachable(m_NewDirection))
		{
			NewCurrentDirection(m_NewDirection);
			return;
		}
		if (m_CurrentTile.Type == PlayFieldGridComponent::TileType::Teleport)
		{
			m_TransformPtr->SetLocalPosition(m_PlayFieldGridPtr->GetTileToTeleportTo(m_CurrentTile).Center);
			return;
		}
		if (not TileReachable(m_CurrentDirection))
		{
			NewCurrentDirection(config::VEC_NEUTRAL);
			return;
		}
	}

	m_TransformPtr->SetLocalPosition(m_PredictedPosition);
}

void pacman::GridMovementComponent::ChangeMovementState(glm::vec2 const& newDirection)
{	
	//if idling go immedeatly no need to wait until you are on a crossing tile
	if (m_CurrentDirection == config::VEC_NEUTRAL and
		TileReachable(newDirection))
	{
		NewCurrentDirection(newDirection);
		return;
	}

	if (newDirection == -m_CurrentDirection and
		TileReachable(newDirection))
	{
		NewCurrentDirection(newDirection);
		return;
	}

	if (newDirection == config::VEC_NEUTRAL)
	{
		NewCurrentDirection(newDirection);
		return;
	}

	m_NewDirection = newDirection;
}

std::vector<glm::vec2> pacman::GridMovementComponent::PossibleDirections()
{
	std::vector<glm::vec2> possibleDirectionVec{};

	glm::vec2 tileCenter
	{
		m_CurrentTile.Center.x,
		m_CurrentTile.Center.y
	};

	glm::vec2 nextTile
	{
		 m_PlayFieldGridPtr->GetTileDimensions().x,
		 m_PlayFieldGridPtr->GetTileDimensions().y
	};

	auto& tileUp = m_PlayFieldGridPtr->GetTile(tileCenter + nextTile * config::VEC_UP);
	if (tileUp.Type == PlayFieldGridComponent::TileType::Pathway or
		tileUp.Type == PlayFieldGridComponent::TileType::Crossing)
	{
		possibleDirectionVec.emplace_back(config::VEC_UP);
	}

	auto& tileDown = m_PlayFieldGridPtr->GetTile(tileCenter + nextTile * config::VEC_DOWN);
	if (tileDown.Type == PlayFieldGridComponent::TileType::Pathway or
		tileDown.Type == PlayFieldGridComponent::TileType::Crossing)
	{
		possibleDirectionVec.emplace_back(config::VEC_DOWN);
	}

	auto& tileLeft = m_PlayFieldGridPtr->GetTile(tileCenter + nextTile * config::VEC_LEFT);
	if (tileLeft.Type == PlayFieldGridComponent::TileType::Pathway or
		tileLeft.Type == PlayFieldGridComponent::TileType::Crossing)
	{
		possibleDirectionVec.emplace_back(config::VEC_LEFT);
	}

	auto& tileRight = m_PlayFieldGridPtr->GetTile(tileCenter + nextTile * config::VEC_RIGHT);
	if (tileRight.Type == PlayFieldGridComponent::TileType::Pathway or
		tileRight.Type == PlayFieldGridComponent::TileType::Crossing)
	{
		possibleDirectionVec.emplace_back(config::VEC_RIGHT);
	}
	return possibleDirectionVec;
}

glm::vec2 const& pacman::GridMovementComponent::GetCurrentDirection() const
{
	return m_CurrentDirection;
}

std::int64_t pacman::GridMovementComponent::ChangeSpeed(std::int64_t const& newSpeed)
{
	std::int64_t speed{ m_Speed };
	m_Speed = newSpeed;
	return speed;
}

bool pacman::GridMovementComponent::TileReachable(glm::vec2 const& direction) const
{
	glm::vec2 tileToCheckPos
	{
		m_CurrentTile.Center.x + m_PlayFieldGridPtr->GetTileDimensions().x * direction.x,
		m_CurrentTile.Center.y + m_PlayFieldGridPtr->GetTileDimensions().y * direction.y
	};

	auto const& tile = m_PlayFieldGridPtr->GetTile(tileToCheckPos);

	if (tile.Type != PlayFieldGridComponent::TileType::Pathway and
		tile.Type != PlayFieldGridComponent::TileType::Crossing and
		tile.Type != PlayFieldGridComponent::TileType::Teleport)
	{
		return false;
	}
	return true;
}

bool pacman::GridMovementComponent::IsCentered() const
{
	if (m_CurrentDirection == config::VEC_DOWN)
	{
		if (m_CurrentPosition.y < m_CurrentTile.Center.y and
			m_PredictedPosition.y >= m_CurrentTile.Center.y)
		{
			return true;
		}
	}
	if (m_CurrentDirection == config::VEC_UP)
	{
		if (m_CurrentPosition.y > m_CurrentTile.Center.y and
			m_PredictedPosition.y <= m_CurrentTile.Center.y)
		{
			return true;
		}
	}
	if (m_CurrentDirection == config::VEC_RIGHT)
	{
		if (m_CurrentPosition.x < m_CurrentTile.Center.x and
			m_PredictedPosition.x >= m_CurrentTile.Center.x)
		{
			return true;
		}
	}
	if (m_CurrentDirection == config::VEC_LEFT)
	{
		if (m_CurrentPosition.x > m_CurrentTile.Center.x and
			m_PredictedPosition.x <= m_CurrentTile.Center.x)
		{
			return true;
		}
	}
	return false;
}

void pacman::GridMovementComponent::NewCurrentDirection(glm::vec2 const& newDirection)
{
	m_CurrentDirection = newDirection;
	m_NewDirection = config::VEC_NEUTRAL;
	NotifyObservers(pacman::events::GRID_DIRECTION_CHANGES);
}
