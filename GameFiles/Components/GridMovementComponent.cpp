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

	m_OldPosition = m_TransformPtr->GetWorldPosition();

	m_CurrentTile = m_PlayFieldGridPtr->GetTile(m_OldPosition);

	if (IsCentered())
	{
		m_TransformPtr->SetLocalPosition(m_CurrentTile.Center);
		if (m_Tag == pacman::tags::BLINKY and m_CurrentTile.Type == PlayFieldGridComponent::TileType::Crossing)
		{
			NotifyObservers(events::GHOST_INPUT_REQUIRED);
		}
		if (m_CurrentTile.Type == PlayFieldGridComponent::TileType::Crossing and
			m_NewDirection != glm::vec2{ 0, 0 } and
			m_CurrentDirection != m_NewDirection and
			TileReachable(m_NewDirection))
		{
			m_CurrentDirection = m_NewDirection;
			m_NewDirection = glm::vec2{ 0, 0 };
			return;
		}
		if (not TileReachable(m_CurrentDirection))
		{
			m_CurrentDirection = glm::vec2{ 0, 0 };
			m_NewDirection = glm::vec2{ 0, 0 };
		}
		if (m_CurrentTile.Type == PlayFieldGridComponent::TileType::Pathway or
			m_CurrentTile.Type == PlayFieldGridComponent::TileType::Crossing)
		{
			return;
		}
	}

	m_TransformPtr->SetLocalPosition(m_PredictedPosition);
}

void pacman::GridMovementComponent::ChangeMovementState(glm::vec2 const& newDirection)
{	
	//if Idling go immedeatly no need to wait until you are on the a crossing tile
	if (m_CurrentDirection == glm::vec2{ 0, 0 } 
		and TileReachable(newDirection))
	{
		m_CurrentDirection = newDirection;
		m_NewDirection = glm::vec2{ 0, 0 };
		return;
	}

	if (newDirection == -m_CurrentDirection)
	{
		m_CurrentDirection = newDirection;
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

	glm::vec2 up{ 0, -1 };
	auto& tileUp = m_PlayFieldGridPtr->GetTile(tileCenter + nextTile * up);
	if (tileUp.Type == PlayFieldGridComponent::TileType::Pathway or
		tileUp.Type == PlayFieldGridComponent::TileType::Crossing)
	{
		possibleDirectionVec.emplace_back(up);
	}

	glm::vec2 down{ 0, 1 };
	auto& tileDown = m_PlayFieldGridPtr->GetTile(tileCenter + nextTile * down);
	if (tileDown.Type == PlayFieldGridComponent::TileType::Pathway or
		tileDown.Type == PlayFieldGridComponent::TileType::Crossing)
	{
		possibleDirectionVec.emplace_back(down);
	}

	glm::vec2 left{ -1, 0 };
	auto& tileLeft = m_PlayFieldGridPtr->GetTile(tileCenter + nextTile * left);
	if (tileLeft.Type == PlayFieldGridComponent::TileType::Pathway or
		tileLeft.Type == PlayFieldGridComponent::TileType::Crossing)
	{
		possibleDirectionVec.emplace_back(left);
	}

	glm::vec2 right{ 1, 0 };
	auto& tileRight = m_PlayFieldGridPtr->GetTile(tileCenter + nextTile * right);
	if (tileRight.Type == PlayFieldGridComponent::TileType::Pathway or
		tileRight.Type == PlayFieldGridComponent::TileType::Crossing)
	{
		possibleDirectionVec.emplace_back(right);
	}
	return possibleDirectionVec;
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
		tile.Type != PlayFieldGridComponent::TileType::Crossing)
	{
		return false;
	}
	return true;
}

bool pacman::GridMovementComponent::IsCentered() const
{
	if (m_CurrentDirection == glm::vec2{ 1, 0 })
	{
		if (m_OldPosition.x < m_CurrentTile.Center.x and
			m_PredictedPosition.x > m_CurrentTile.Center.x)
		{
			return true;
		}
	}
	if (m_CurrentDirection == glm::vec2{ -1, 0 })
	{
		if (m_OldPosition.x > m_CurrentTile.Center.x and
			m_PredictedPosition.x < m_CurrentTile.Center.x)
		{
			return true;
		}
	}
	if (m_CurrentDirection == glm::vec2{ 0, 1 })
	{
		if (m_OldPosition.y < m_CurrentTile.Center.y and
			m_PredictedPosition.y > m_CurrentTile.Center.y)
		{
			return true;
		}
	}
	if (m_CurrentDirection == glm::vec2{ 0, -1 })
	{
		if (m_OldPosition.y > m_CurrentTile.Center.y and
			m_PredictedPosition.y < m_CurrentTile.Center.y)
		{
			return true;
		}
	}
	return false;
}
