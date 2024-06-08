#include "PacmanFSM.h"
#include "GameTime.h"
#include "ServiceLocator.h"

pacman::PacmanFSMComponent::PacmanFSMComponent(amu::GameObject* ownerObjectPtr)
	: Component(ownerObjectPtr)
	, Subject(ownerObjectPtr)
{
	m_GridMoveCompPtr = GetComponentOwner()->GetComponent<GridMovementComponent>();

	m_PickupStatesUPtrVec.emplace_back(std::make_unique<WaitingStateSmallPickupOverlap>());
	m_PickupStatesUPtrVec.emplace_back(std::make_unique<HasEatenStateSmallPickupOverlap>());

	m_CurrentStatePickupPtr = GetPickupState<WaitingStateSmallPickupOverlap>();

	m_PMStatesUPtrVec.emplace_back(std::make_unique<CollectingState>());
	m_PMStatesUPtrVec.emplace_back(std::make_unique<DyingState>());

	m_CurrentStatePtr = GetState<CollectingState>();
}

void pacman::PacmanFSMComponent::HandleInput(glm::vec2 const& direction)
{
	m_CurrentStatePtr->HandleInput(direction, this);
}

void pacman::PacmanFSMComponent::HandleOverlap(amu::CollisionComponent* otherColliderPtr)
{
	if (BaseStatePacman* newState{ m_CurrentStatePtr->HandleOverlap(otherColliderPtr, this) }; newState != nullptr)
	{
		m_CurrentStatePtr->OnExit(this);
		m_CurrentStatePtr = newState;
		m_CurrentStatePtr->OnEnter(this);
	}
}

void pacman::PacmanFSMComponent::Update()
{
	if (BaseStatePacman* newState{ m_CurrentStatePtr->Update(amu::GameTime::GetInstance().GetDeltaTime(), this)}; newState != nullptr)
	{
		m_CurrentStatePtr->OnExit(this);
		m_CurrentStatePtr = newState;
		m_CurrentStatePtr->OnEnter(this);
	}
}

pacman::BaseStatePickupOverlap* pacman::PacmanFSMComponent::GetCurrentPickupState()
{
	return m_CurrentStatePickupPtr;
}

void pacman::PacmanFSMComponent::SetCurrentPickupState(BaseStatePickupOverlap* newStatePtr)
{
	m_CurrentStatePickupPtr = newStatePtr;
}

pacman::GridMovementComponent* pacman::PacmanFSMComponent::GetGridMove()
{
	return m_GridMoveCompPtr;
}

pacman::BaseStatePickupOverlap* pacman::WaitingStateSmallPickupOverlap::Update(double, PacmanFSMComponent*)
{
	return nullptr;
}

pacman::BaseStatePickupOverlap* pacman::WaitingStateSmallPickupOverlap::HandleOverlap(PacmanFSMComponent* ownerPtr)
{
	return ownerPtr->GetPickupState<HasEatenStateSmallPickupOverlap>();
}

void pacman::HasEatenStateSmallPickupOverlap::OnEnter()
{
	m_Timer = 0.0;
	auto& pm_chomp = resources::sound::PACMAN_CHOMP;
	amu::ServiceLocator::GetInstance().GetSoundSystem()->RequestSoundEffect(pm_chomp.Id, pm_chomp.FilePath, pm_chomp.Volume, pm_chomp.Loops);
}

void pacman::HasEatenStateSmallPickupOverlap::OnExit()
{
	auto& pm_chomp = resources::sound::PACMAN_CHOMP;
	amu::ServiceLocator::GetInstance().GetSoundSystem()->RequestStopSoundEffect(pm_chomp.Id);
}

pacman::BaseStatePickupOverlap* pacman::HasEatenStateSmallPickupOverlap::Update(double elapsedSec, PacmanFSMComponent* ownerPtr)
{
	m_Timer += elapsedSec;
	if (m_Timer >= m_MaxTime)
	{
		return ownerPtr->GetPickupState<WaitingStateSmallPickupOverlap>();
	}
	return nullptr;
}

pacman::BaseStatePickupOverlap* pacman::HasEatenStateSmallPickupOverlap::HandleOverlap(PacmanFSMComponent*)
{
	m_Timer = 0.0;

	return nullptr;
}

pacman::BaseStatePacman* pacman::BaseStatePacman::Update(double elapsedSec, PacmanFSMComponent* ownerPtr)
{
	BaseStatePickupOverlap* currentStatePtr{ ownerPtr->GetCurrentPickupState() };
	if (auto newState{ currentStatePtr->Update(elapsedSec, ownerPtr) }; newState != nullptr)
	{
		currentStatePtr->OnExit();
		ownerPtr->SetCurrentPickupState(newState);
		ownerPtr->GetCurrentPickupState()->OnEnter();
	}
	return nullptr;
}

pacman::BaseStatePacman* pacman::BaseStatePacman::HandleOverlap(amu::CollisionComponent* otherColliderPtr, PacmanFSMComponent* ownerPtr)
{
	std::string_view otherTag{ otherColliderPtr->GetComponentOwner()->GetTag() };
	if (otherTag == tags::PICKUP_SMALL or
		otherTag == tags::PICKUP_BIG)
	{
		BaseStatePickupOverlap* currentStatePtr{ ownerPtr->GetCurrentPickupState() };
		if (auto newState{ currentStatePtr->HandleOverlap(ownerPtr) }; newState != nullptr)
		{
			currentStatePtr->OnExit();
			ownerPtr->SetCurrentPickupState(newState);
			ownerPtr->GetCurrentPickupState()->OnEnter();
		}
	}
	return nullptr;
}

void pacman::CollectingState::OnEnter(PacmanFSMComponent*)
{
}

void pacman::CollectingState::OnExit(PacmanFSMComponent*)
{
}

void pacman::CollectingState::HandleInput(glm::vec2 const& direction, PacmanFSMComponent* ownerPtr)
{
	ownerPtr->GetGridMove()->ChangeMovementState(direction);
	ownerPtr->NotifyObservers(events::PACMAN_HIT_GHOST);
}

pacman::BaseStatePacman* pacman::CollectingState::Update(double elapsedSec, PacmanFSMComponent* ownerPtr)
{
	BaseStatePacman::Update(elapsedSec, ownerPtr);
	return nullptr;
}

pacman::BaseStatePacman* pacman::CollectingState::HandleOverlap(amu::CollisionComponent* otherColliderPtr, PacmanFSMComponent* ownerPtr)
{
	BaseStatePacman::HandleOverlap(otherColliderPtr, ownerPtr);
	std::string_view otherTag{ otherColliderPtr->GetComponentOwner()->GetTag() };
	if (otherTag == tags::BLINKY)
	{
		return ownerPtr->GetState<DyingState>();
	}
	if (otherTag == tags::PICKUP_SMALL)
	{
		ownerPtr->NotifyObservers(events::PACMAN_EAT_SMALL_PICKUP);
	}
	else if (otherTag == tags::PICKUP_BIG)
	{
		ownerPtr->NotifyObservers(events::PACMAN_EAT_BIG_PICKUP);
	}
	return nullptr;
}

void pacman::DyingState::OnEnter(PacmanFSMComponent* ownerPtr)
{
	ownerPtr->GetGridMove()->ChangeMovementState(config::VEC_NEUTRAL);
}

void pacman::DyingState::OnExit(PacmanFSMComponent*)
{
}

void pacman::DyingState::HandleInput(glm::vec2 const&, PacmanFSMComponent*)
{
}

pacman::BaseStatePacman* pacman::DyingState::Update(double elapsedSec, PacmanFSMComponent* ownerPtr)
{
	BaseStatePacman::Update(elapsedSec, ownerPtr);
	return nullptr;
}

pacman::BaseStatePacman* pacman::DyingState::HandleOverlap(amu::CollisionComponent* otherColliderPtr, PacmanFSMComponent* ownerPtr)
{
	BaseStatePacman::HandleOverlap(otherColliderPtr, ownerPtr);
	return nullptr;
}