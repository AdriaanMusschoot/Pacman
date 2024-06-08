#include "GhostFSM.h"
#include "GameTime.h"

pacman::GhostFSMComponent::GhostFSMComponent(amu::GameObject* ownerObjectPtr, amu::TransformComponent* pacmanTransformPtr)
	: Component(ownerObjectPtr)
	, Subject(ownerObjectPtr)
	, m_PacmanTransformPtr{ pacmanTransformPtr }
{
	m_TransformPtr = GetComponentOwner()->GetComponent<amu::TransformComponent>();
	m_GridMovementPtr = GetComponentOwner()->GetComponent<GridMovementComponent>();
	m_AIPtr = GetComponentOwner()->GetComponent<BlinkyAIComponent>();
	assert(m_AIPtr);
	assert(m_GridMovementPtr);
	m_GridMovementPtr->ChangeMovementState(config::VEC_LEFT);
	m_GridMovementPtr->AddObserver(this);

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
	if (BaseGhostState* newStatePtr{ m_CurrentGhostStatePtr->OnNotify(eventType, subjectPtr, this) }; newStatePtr != nullptr)
	{
		m_CurrentGhostStatePtr->OnExit(this);
		m_CurrentGhostStatePtr = newStatePtr;
		m_CurrentGhostStatePtr->OnEnter(this);
	}
}

void pacman::GhostFSMComponent::SetPreviousDirection(glm::vec2 const& direction)
{
	m_PreviousDirection = direction;
}

glm::vec2 const& pacman::GhostFSMComponent::GetPreviousDirection()
{
	return m_GridMovementPtr->GetCurrentDirection();
}

glm::vec2 const& pacman::GhostFSMComponent::GetPacmanPosition()
{
	return m_PacmanTransformPtr->GetWorldPosition();
}

glm::vec2 const& pacman::GhostFSMComponent::GetGhostPosition()
{
	return m_TransformPtr->GetWorldPosition();
}

pacman::GridMovementComponent* pacman::GhostFSMComponent::GetGridMove() const
{
	return m_GridMovementPtr;
}

pacman::BaseAIComponent* pacman::GhostFSMComponent::GetAI() const
{
	return m_AIPtr;
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

pacman::BaseGhostState* pacman::HuntingPacmanState::OnNotify(amu::IObserver::Event eventType, amu::Subject*, GhostFSMComponent* ownerPtr)
{
	if (eventType == events::PACMAN_EAT_BIG_PICKUP)
	{
		return ownerPtr->GetState<AvoidingPacmanState>();
	}
	else if (eventType == events::GHOST_INPUT_REQUIRED)
	{
		glm::vec2 const& pacmanPos = ownerPtr->GetPacmanPosition();
		glm::vec2 const& ghostPos = ownerPtr->GetGhostPosition();
		glm::vec2 const& previousDir = ownerPtr->GetPreviousDirection();
		GridMovementComponent* gridMovePtr{ ownerPtr->GetGridMove() };
		std::vector<glm::vec2> possibleDirectionVec{ gridMovePtr->PossibleDirections() };
		glm::vec2 const& optimalDirection{ ownerPtr->GetAI()->GetOptimalDirectionToPacman(possibleDirectionVec, pacmanPos, ghostPos, previousDir) };
		if (optimalDirection != config::VEC_INVALID)
		{
			gridMovePtr->ChangeMovementState(optimalDirection);
			ownerPtr->SetPreviousDirection(optimalDirection);
		}
		else
		{
			auto& safetyDirection = possibleDirectionVec[0];
			gridMovePtr->ChangeMovementState(safetyDirection);
			ownerPtr->SetPreviousDirection(optimalDirection);
		}
	}
	else if (eventType == events::GRID_DIRECTION_CHANGES)
	{
		ownerPtr->NotifyObservers(events::GRID_DIRECTION_CHANGES);
	}
	return nullptr;
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

pacman::BaseGhostState* pacman::AvoidingPacmanState::OnNotify(amu::IObserver::Event eventType, amu::Subject* , GhostFSMComponent* ownerPtr)
{
	if (eventType == events::PACMAN_EAT_BIG_PICKUP)
	{
		m_Timer = 0.0;
		return nullptr;
	}
	if (eventType == events::GHOST_INPUT_REQUIRED)
	{
		glm::vec2 const& pacmanPos = ownerPtr->GetPacmanPosition();
		glm::vec2 const& ghostPos = ownerPtr->GetGhostPosition();
		glm::vec2 const& previousDir = ownerPtr->GetPreviousDirection();
		GridMovementComponent* gridMovePtr{ ownerPtr->GetGridMove() };
		std::vector<glm::vec2> possibleDirectionVec{ gridMovePtr->PossibleDirections() };
		glm::vec2 const& optimalDirection{ ownerPtr->GetAI()->GetOptimalDirectionFromPacman(possibleDirectionVec, pacmanPos, ghostPos, previousDir) };
		if (optimalDirection != config::VEC_INVALID)
		{
			gridMovePtr->ChangeMovementState(optimalDirection);
			ownerPtr->SetPreviousDirection(optimalDirection);
		}
		else
		{
			auto& safetyDirection = possibleDirectionVec[0];
			gridMovePtr->ChangeMovementState(safetyDirection);
			ownerPtr->SetPreviousDirection(optimalDirection);
		}
	}
	return nullptr;
}