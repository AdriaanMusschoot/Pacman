#include "GhostFSM.h"
#include "GameTime.h"

pacman::GhostFSMComponent::GhostFSMComponent(amu::GameObject* ownerObjectPtr, amu::GameObject* pacmanTransformPtr)
	: Component(ownerObjectPtr)
	, Subject(ownerObjectPtr)
	, m_PacmanPtr{ pacmanTransformPtr }
{
	m_TransformPtr = GetComponentOwner()->GetComponent<amu::TransformComponent>();
	m_GridMovementPtr = GetComponentOwner()->GetComponent<GridMovementComponent>();
	m_AIPtr = GetComponentOwner()->GetComponent<BaseAIComponent>();
	assert(m_AIPtr);
	assert(m_GridMovementPtr);
	m_GridMovementPtr->ChangeMovementState(config::VEC_LEFT);
	m_GridMovementPtr->AddObserver(this);

	m_GhostStateUPtrVec.emplace_back(std::make_unique<HuntingPacmanState>());
	m_GhostStateUPtrVec.emplace_back(std::make_unique<AvoidingPacmanState>());
	m_GhostStateUPtrVec.emplace_back(std::make_unique<EatenByPacmanState>());

	m_CurrentGhostStatePtr = GetState<HuntingPacmanState>();

	m_SpawnPos = m_TransformPtr->GetWorldPosition();
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
	if (eventType == events::PACMAN_DYING_ANIM_FINISHED)
	{
		m_CurrentGhostStatePtr->OnExit(this);
		m_CurrentGhostStatePtr = GetState<HuntingPacmanState>();
		m_CurrentGhostStatePtr->OnEnter(this);
		m_TransformPtr->SetLocalPosition(m_SpawnPos);
		m_GridMovementPtr->Spawn(m_SpawnPos);
		m_GridMovementPtr->ChangeMovementState(config::VEC_NEUTRAL);
		m_GridMovementPtr->ChangeMovementState(config::VEC_LEFT);
	}

	if (BaseGhostState* newStatePtr{ m_CurrentGhostStatePtr->OnNotify(eventType, subjectPtr, this) }; newStatePtr != nullptr)
	{
		m_CurrentGhostStatePtr->OnExit(this);
		m_CurrentGhostStatePtr = newStatePtr;
		m_CurrentGhostStatePtr->OnEnter(this);
	}
}

pacman::BaseGhostState* pacman::GhostFSMComponent::GetGhostState() const
{
	return m_CurrentGhostStatePtr;
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
	return m_PacmanPtr->GetComponent<amu::TransformComponent>()->GetWorldPosition();
}

glm::vec2 const& pacman::GhostFSMComponent::GetPacmanDirection()
{
	return m_PacmanPtr->GetComponent<GridMovementComponent>()->GetCurrentDirection();
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

void pacman::HuntingPacmanState::OnEnter(GhostFSMComponent* ownerPtr)
{
	ownerPtr->NotifyObservers(events::GHOST_ATTACK);
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
		GridMovementComponent* gridMovePtr{ ownerPtr->GetGridMove() };
		std::vector<glm::vec2> possibleDirectionVec{ gridMovePtr->PossibleDirections() };
		glm::vec2 const& optimalDirection{ ownerPtr->GetAI()->GetOptimalDirectionToPacman(possibleDirectionVec, ownerPtr) };
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

void pacman::AvoidingPacmanState::OnEnter(GhostFSMComponent* ownerPtr)
{
	GridMovementComponent* gridMovementPtr{ ownerPtr->GetGridMove() };
	gridMovementPtr->ChangeMovementState(-gridMovementPtr->GetCurrentDirection());
	ownerPtr->NotifyObservers(events::GHOST_PANICK);
}

void pacman::AvoidingPacmanState::OnExit(GhostFSMComponent* )
{
}

void pacman::AvoidingPacmanState::HandleInput(glm::vec2 const& , GhostFSMComponent* )
{
}

pacman::BaseGhostState* pacman::AvoidingPacmanState::Update(double, GhostFSMComponent*)
{
	return nullptr;
}

pacman::BaseGhostState* pacman::AvoidingPacmanState::HandleOverlap(amu::CollisionComponent* otherColliderPtr, GhostFSMComponent* ownerPtr)
{
	std::string_view otherTag{ otherColliderPtr->GetComponentOwner()->GetTag() };
	if (otherTag == tags::PACMAN)
	{
		return ownerPtr->GetState<EatenByPacmanState>();
	}
	return nullptr;
}

pacman::BaseGhostState* pacman::AvoidingPacmanState::OnNotify(amu::IObserver::Event eventType, amu::Subject* , GhostFSMComponent* ownerPtr)
{
	if (eventType == events::GHOST_INPUT_REQUIRED)
	{
		GridMovementComponent* gridMovePtr{ ownerPtr->GetGridMove() };
		std::vector<glm::vec2> possibleDirectionVec{ gridMovePtr->PossibleDirections() };
		glm::vec2 const& optimalDirection{ ownerPtr->GetAI()->GetOptimalDirectionFromPacman(possibleDirectionVec, ownerPtr) };
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
	else if (eventType == events::PACMAN_COLLECT)
	{
		return ownerPtr->GetState<HuntingPacmanState>();
	}
	else if (eventType == events::PACMAN_EAT_BIG_PICKUP)
	{
		ownerPtr->NotifyObservers(events::GHOST_PANICK);
	}
	return nullptr;
}

void pacman::EatenByPacmanState::OnEnter(GhostFSMComponent* ownerPtr)
{
	m_StartSpeed = ownerPtr->GetGridMove()->ChangeSpeed(config::RETURN_TO_SPAWN_SPEED);
	ownerPtr->NotifyObservers(events::GHOST_RUSHING_TO_SPAWN);
}

void pacman::EatenByPacmanState::OnExit(GhostFSMComponent* ownerPtr)
{
	ownerPtr->GetGridMove()->ChangeSpeed(m_StartSpeed);
}

void pacman::EatenByPacmanState::HandleInput(glm::vec2 const&, GhostFSMComponent*)
{
}

pacman::BaseGhostState* pacman::EatenByPacmanState::Update(double, GhostFSMComponent* ownerPtr)
{
	glm::vec2 const& ghostPos = ownerPtr->GetGhostPosition();
	if (ownerPtr->GetAI()->IsAtSpawnPos(ghostPos))
	{
		return ownerPtr->GetState<HuntingPacmanState>();
	}
	return nullptr;
}

pacman::BaseGhostState* pacman::EatenByPacmanState::HandleOverlap(amu::CollisionComponent*, GhostFSMComponent*)
{
	return nullptr;
}

pacman::BaseGhostState* pacman::EatenByPacmanState::OnNotify(amu::IObserver::Event eventType, amu::Subject*, GhostFSMComponent* ownerPtr)
{
	if (eventType == events::GHOST_INPUT_REQUIRED)
	{
		GridMovementComponent* gridMovePtr{ ownerPtr->GetGridMove() };
		std::vector<glm::vec2> possibleDirectionVec{ gridMovePtr->PossibleDirections() };
		glm::vec2 const& optimalDirection{ ownerPtr->GetAI()->GetOptimalDirectionToSpawn(possibleDirectionVec, ownerPtr) };
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
