#include "GhostFSM.h"
#include "GameTime.h"

pacman::GhostFSMComponent::GhostFSMComponent(amu::GameObject* ownerObjectPtr, amu::TransformComponent* pacmanTransformPtr)
	: Component(ownerObjectPtr)
	, m_PacmanTransformPtr{ pacmanTransformPtr }
{
	m_TransformPtr = GetComponentOwner()->GetComponent<amu::TransformComponent>();
	m_GridMovementPtr = GetComponentOwner()->GetComponent<GridMovementComponent>();
	assert(m_GridMovementPtr);
	m_GridMovementPtr->ChangeMovementState(config::VEC_LEFT);


	m_GhostStateUPtrVec.emplace_back(std::make_unique<HuntingPacmanState>());
	m_GhostStateUPtrVec.emplace_back(std::make_unique<AvoidingPacmanState>());

	m_CurrentGhostStatePtr = GetState<HuntingPacmanState>();
}

void pacman::GhostFSMComponent::HandleInput(glm::vec2 const& direction)
{
	m_CurrentGhostStatePtr->HandleInput(direction, this);
}

void pacman::GhostFSMComponent::HandleOverlap(amu::CollisionComponent* otherColliderPtr)
{
	if (BaseGhostState* newStatePtr{ m_CurrentGhostStatePtr->HandleOverlap(otherColliderPtr, this) }; newStatePtr != nullptr)
	{
		m_CurrentGhostStatePtr->OnExit(this);
		m_CurrentGhostStatePtr = newStatePtr;
		m_CurrentGhostStatePtr->OnEnter(this);
	}
}

void pacman::GhostFSMComponent::Update()
{
	if (BaseGhostState* newStatePtr{ m_CurrentGhostStatePtr->Update(amu::GameTime::GetInstance().GetDeltaTime(), this)}; newStatePtr != nullptr)
	{
		m_CurrentGhostStatePtr->OnExit(this);
		m_CurrentGhostStatePtr = newStatePtr;
		m_CurrentGhostStatePtr->OnEnter(this);
	}
}

void pacman::GhostFSMComponent::OnNotify(amu::IObserver::Event eventType, amu::Subject* subjectPtr)
{
	if (eventType == events::GHOST_INPUT_REQUIRED)
	{
		std::vector<glm::vec2> possibleDirectionVec{ m_GridMovementPtr->PossibleDirections() };
		glm::vec2 const& optimalDirection{ m_CurrentGhostStatePtr->GetOptimalDirection(possibleDirectionVec, this) };
		if (optimalDirection != config::VEC_INVALID)
		{
			m_GridMovementPtr->ChangeMovementState(optimalDirection);
			m_PreviousDirection = optimalDirection;
		}
		else
		{
			auto& safetyDirection = possibleDirectionVec[0];
			m_GridMovementPtr->ChangeMovementState(safetyDirection);
			m_PreviousDirection = optimalDirection;
		}
	}

	if (BaseGhostState* newStatePtr{ m_CurrentGhostStatePtr->OnNotify(eventType, subjectPtr, this) }; newStatePtr != nullptr)
	{
		m_CurrentGhostStatePtr->OnExit(this);
		m_CurrentGhostStatePtr = newStatePtr;
		m_CurrentGhostStatePtr->OnEnter(this);
	}
}

glm::vec2 const& pacman::GhostFSMComponent::GetPreviousDirection()
{
	return m_GridMovementPtr->GetCurrentDirection();
}

glm::vec2 const& pacman::GhostFSMComponent::GetPacmanPosition()
{
	return m_TransformPtr->GetWorldPosition();
}

glm::vec2 const& pacman::GhostFSMComponent::GetGhostPosition()
{
	return m_PacmanTransformPtr->GetWorldPosition();
}

pacman::BaseGhostState::Axis pacman::BaseGhostState::GetOptimalAxis(float deltaX, float deltaY) const
{
	if (std::abs(deltaX) > std::abs(deltaY))
	{
		return Axis::X;
	}
	else
	{
		return Axis::Y;
	}
}

glm::vec2 pacman::BaseGhostState::GetOptimalHorizontalDirection(float deltaX) const
{
	if (deltaX > 0)
	{
		return config::VEC_RIGHT;
	}
	else
	{
		return config::VEC_LEFT;
	}
}

glm::vec2 pacman::BaseGhostState::GetOptimalVerticalDirection(float deltaY) const
{
	if (deltaY > 0)
	{
		return config::VEC_DOWN;
	}
	else
	{
		return config::VEC_UP;
	}
}


void pacman::HuntingPacmanState::OnEnter(GhostFSMComponent*)
{
}

void pacman::HuntingPacmanState::OnExit(GhostFSMComponent*)
{
}

void pacman::HuntingPacmanState::HandleInput(glm::vec2 const&, GhostFSMComponent*)
{
}

pacman::BaseGhostState* pacman::HuntingPacmanState::Update(double, GhostFSMComponent*)
{
	return nullptr;
}

pacman::BaseGhostState* pacman::HuntingPacmanState::HandleOverlap(amu::CollisionComponent*, GhostFSMComponent*)
{
	return nullptr;
}

pacman::BaseGhostState* pacman::HuntingPacmanState::OnNotify(amu::IObserver::Event, amu::Subject*, GhostFSMComponent*)
{
	return nullptr;
}

glm::vec2 const& pacman::HuntingPacmanState::GetOptimalDirection(std::vector<glm::vec2> const& possibleDirections, GhostFSMComponent* ownerPtr)
{
	auto& pacmanPosition = ownerPtr->GetPacmanPosition();
	auto& ghostPosition = ownerPtr->GetGhostPosition();
	float deltaX = pacmanPosition.x - ghostPosition.x;
	float deltaY = pacmanPosition.y - ghostPosition.y;

	if (GetOptimalAxis(deltaX, deltaY) == Axis::X)
	{
		m_PreferredDirectionVec[0] = (-GetOptimalVerticalDirection(deltaY));
		m_PreferredDirectionVec[1] = (-GetOptimalHorizontalDirection(deltaX));
		m_PreferredDirectionVec[2] = (GetOptimalVerticalDirection(deltaY));
		m_PreferredDirectionVec[3] = (GetOptimalHorizontalDirection(deltaX));
	}
	else
	{
		m_PreferredDirectionVec[0] = (-GetOptimalHorizontalDirection(deltaX));
		m_PreferredDirectionVec[1] = (-GetOptimalVerticalDirection(deltaY));
		m_PreferredDirectionVec[2] = (GetOptimalHorizontalDirection(deltaX));
		m_PreferredDirectionVec[3] = (GetOptimalVerticalDirection(deltaY));
	}
	for (glm::vec2 const& preferredDirection : m_PreferredDirectionVec)
	{
		if (preferredDirection == -ownerPtr->GetPreviousDirection())
		{
			continue;
		}

		if (std::any_of(possibleDirections.begin(), possibleDirections.end(),
			[&](glm::vec2 const& possibleDirection)
			{
				return possibleDirection == preferredDirection;
			}))
		{
			return preferredDirection;
		}
	}

	return config::VEC_INVALID;
}

void pacman::AvoidingPacmanState::OnEnter(GhostFSMComponent* )
{
}

void pacman::AvoidingPacmanState::OnExit(GhostFSMComponent* )
{
}

void pacman::AvoidingPacmanState::HandleInput(glm::vec2 const& , GhostFSMComponent* )
{
}

pacman::BaseGhostState* pacman::AvoidingPacmanState::Update(double elapsedSec, GhostFSMComponent* ownerPtr)
{
	m_Timer += elapsedSec;
	if (m_Timer > m_MaxTime)
	{
		return ownerPtr->GetState<HuntingPacmanState>();
	}
	return nullptr;
}

pacman::BaseGhostState* pacman::AvoidingPacmanState::HandleOverlap(amu::CollisionComponent* , GhostFSMComponent* )
{
	return nullptr;
}

pacman::BaseGhostState* pacman::AvoidingPacmanState::OnNotify(amu::IObserver::Event , amu::Subject* , GhostFSMComponent* )
{
	return nullptr;
}

glm::vec2 const& pacman::AvoidingPacmanState::GetOptimalDirection(std::vector<glm::vec2> const& possibleDirections, GhostFSMComponent* ownerPtr)
{
	auto& pacmanPosition = ownerPtr->GetPacmanPosition();
	auto& ghostPosition = ownerPtr->GetGhostPosition();
	float deltaX = pacmanPosition.x - ghostPosition.x;
	float deltaY = pacmanPosition.y - ghostPosition.y;


	if (GetOptimalAxis(deltaX, deltaY) == Axis::X)
	{
		m_PreferredDirectionVec[0] = (GetOptimalHorizontalDirection(deltaX));
		m_PreferredDirectionVec[1] = (GetOptimalVerticalDirection(deltaY));
		m_PreferredDirectionVec[2] = (-GetOptimalHorizontalDirection(deltaX));
		m_PreferredDirectionVec[3] = (-GetOptimalVerticalDirection(deltaY));
	}
	else
	{
		m_PreferredDirectionVec[0] = (GetOptimalVerticalDirection(deltaY));
		m_PreferredDirectionVec[1] = (GetOptimalHorizontalDirection(deltaX));
		m_PreferredDirectionVec[2] = (-GetOptimalVerticalDirection(deltaY));
		m_PreferredDirectionVec[3] = (-GetOptimalHorizontalDirection(deltaX));
	}
	for (glm::vec2 const& preferredDirection : m_PreferredDirectionVec)
	{
		if (preferredDirection == -ownerPtr->GetPreviousDirection())
		{
			continue;
		}

		if (std::any_of(possibleDirections.begin(), possibleDirections.end(),
			[&](glm::vec2 const& possibleDirection)
			{
				return possibleDirection == preferredDirection;
			}))
		{
			return preferredDirection;
		}
	}

	return config::VEC_INVALID;
}
