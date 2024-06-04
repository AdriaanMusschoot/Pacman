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
		if (m_CurrentTile.Type == PlayFieldGridComponent::TileType::Crossing and
			m_NewDirection != glm::vec2{ 0, 0 } and
			m_CurrentDirection != m_NewDirection and
			TileReachable(m_NewDirection))
		{
			m_TransformPtr->SetLocalPosition(m_CurrentTile.Center);
			m_CurrentDirection = m_NewDirection;
			m_NewDirection = glm::vec2{ 0, 0 };
			return;
		}
		if (not TileReachable(m_CurrentDirection))
		{
			m_TransformPtr->SetLocalPosition(m_CurrentTile.Center);
			m_CurrentDirection = glm::vec2{ 0, 0 };
			m_NewDirection = glm::vec2{ 0, 0 };
		}
		if (m_CurrentTile.Type == PlayFieldGridComponent::TileType::Pathway or
			m_CurrentTile.Type == PlayFieldGridComponent::TileType::Crossing)
		{
			m_TransformPtr->SetLocalPosition(m_CurrentTile.Center);
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
