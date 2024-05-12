#include "GridMovementComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "GameTime.h"

pacman::GridMovementComponent::GridMovementComponent(amu::GameObject * gameObjectPtr, PlayFieldGridComponent* playFieldGridPtr, std::int64_t const& speed)
	: amu::Component(gameObjectPtr)
	, m_PlayFieldGridPtr{ playFieldGridPtr }
	, m_TransformPtr{ GetComponentOwner()->GetComponent<amu::TransformComponent>() }
	, m_Speed{ speed }
	, m_CurrentTile{ playFieldGridPtr->GetTile(m_TransformPtr->GetWorldPosition()) }
{
	GetComponentOwner()->AddComponent<pacman::DistanceComponent>(GetComponentOwner());
	m_DistanceComponentPtr = GetComponentOwner()->GetComponent<pacman::DistanceComponent>();
}

void pacman::GridMovementComponent::Update()
{
	if (not m_TransformPtr)
	{
		return;
	}

	double const& deltaTime = amu::GameTime::GetInstance().GetDeltaTime();
	glm::vec2 offset{ m_CurrentDirection.x * m_Speed * deltaTime, m_CurrentDirection.y * m_Speed * deltaTime };
	m_TransformPtr->SetLocalPosition(m_TransformPtr->GetLocalPosition() + offset);

	m_CurrentTile = m_PlayFieldGridPtr->GetTile(m_TransformPtr->GetWorldPosition());

	if (m_CurrentTile.Type == PlayFieldGridComponent::TileType::Crossing and
		m_NewDirection != glm::vec2{ 0, 0 } and
		TileReachable(m_NewDirection) and
		m_DistanceComponentPtr->Check(m_CurrentTile.Center, m_TransformPtr->GetWorldPosition(), 1))
	{
		m_CurrentDirection = m_NewDirection;
		m_NewDirection = glm::vec2{ 0, 0 };
	}

	if (not TileReachable(m_CurrentDirection) and 
		m_DistanceComponentPtr->Check(m_CurrentTile.Center, m_TransformPtr->GetWorldPosition(), 1))
	{
		m_CurrentDirection = glm::vec2{ 0, 0 };
	}
}

void pacman::GridMovementComponent::ChangeMovementState(glm::vec2 const& newDirection)
{	
	//if Idling go immedeatly no need to wait until you are on the a crossing tile
	if (m_CurrentDirection == glm::vec2{ 0, 0 } 
		and TileReachable(newDirection))
	{
		m_CurrentDirection = newDirection;
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
	glm::vec2 const& worldPos = m_TransformPtr->GetWorldPosition();

	glm::vec2 tileToCheckPos
	{
		worldPos.x + m_PlayFieldGridPtr->GetTileDimensions().x * direction.x,
		worldPos.y + m_PlayFieldGridPtr->GetTileDimensions().y * direction.y
	};

	auto const& tile = m_PlayFieldGridPtr->GetTile(tileToCheckPos);

	if (tile.Type != PlayFieldGridComponent::TileType::Pathway and
		tile.Type != PlayFieldGridComponent::TileType::Crossing)
	{
		return false;
	}
	return true;
}
