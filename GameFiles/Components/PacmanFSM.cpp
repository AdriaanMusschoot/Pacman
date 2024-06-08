#include "PacmanFSM.h"
#include "GameTime.h"
#include "ServiceLocator.h"

pacman::PacmanFSMComponent::PacmanFSMComponent(amu::GameObject* ownerObjectPtr)
	: Component(ownerObjectPtr)
	, Subject(ownerObjectPtr)
	, m_StatePickupUPtr{ std::make_unique<WaitingStateSmallPickupOverlap>() }

{
	m_GridMoveCompPtr = GetComponentOwner()->GetComponent<GridMovementComponent>();
	m_PMStatesUPtr.emplace_back(std::make_unique<CollectingState>());
	m_PMStatesUPtr.emplace_back(std::make_unique<DyingState>());

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
	std::string_view otherTag{ otherColliderPtr->GetComponentOwner()->GetTag() };
	if (otherTag == tags::PICKUP_SMALL or
		otherTag == tags::PICKUP_BIG)
	{
		if (auto newState{ std::move(m_StatePickupUPtr->HandleOverlap()) }; newState != nullptr)
		{
			m_StatePickupUPtr->OnExit();
			m_StatePickupUPtr = std::move(newState);
			m_StatePickupUPtr->OnEnter();
		}
	}
	if (otherTag == tags::PICKUP_SMALL)
	{
		NotifyObservers(events::PACMAN_EAT_SMALL_PICKUP);
	}
	else if (otherTag == tags::PICKUP_BIG)
	{
		NotifyObservers(events::PACMAN_EAT_BIG_PICKUP);
	}
	if (otherTag == tags::BLINKY)
	{
		NotifyObservers(events::PACMAN_HIT_GHOST);
	}
}

void pacman::PacmanFSMComponent::Update()
{
	if (auto newState{ std::move(m_StatePickupUPtr->Update(amu::GameTime::GetInstance().GetDeltaTime())) }; newState != nullptr)
	{
		m_StatePickupUPtr->OnExit();
		m_StatePickupUPtr = std::move(newState);
		m_StatePickupUPtr->OnEnter();
	}
}

pacman::GridMovementComponent* pacman::PacmanFSMComponent::GetGridMove()
{
	return m_GridMoveCompPtr;
}

std::unique_ptr<pacman::BaseStatePickupOverlap> pacman::WaitingStateSmallPickupOverlap::Update(double)
{
	return nullptr;
}

std::unique_ptr<pacman::BaseStatePickupOverlap> pacman::WaitingStateSmallPickupOverlap::HandleOverlap()
{
	return std::make_unique<HasEatenStateSmallPickupOverlap>();
}

void pacman::HasEatenStateSmallPickupOverlap::OnEnter()
{
	auto& pm_chomp = resources::sound::PACMAN_CHOMP;
	amu::ServiceLocator::GetInstance().GetSoundSystem()->RequestSoundEffect(pm_chomp.Id, pm_chomp.FilePath, pm_chomp.Volume, pm_chomp.Loops);
}

void pacman::HasEatenStateSmallPickupOverlap::OnExit()
{
	auto& pm_chomp = resources::sound::PACMAN_CHOMP;
	amu::ServiceLocator::GetInstance().GetSoundSystem()->RequestStopSoundEffect(pm_chomp.Id);
}

std::unique_ptr<pacman::BaseStatePickupOverlap> pacman::HasEatenStateSmallPickupOverlap::Update(double elapsedTime)
{
	m_Timer += elapsedTime;
	if (m_Timer >= m_MaxTime)
	{
		return std::make_unique<WaitingStateSmallPickupOverlap>();
	}
	return nullptr;
}

std::unique_ptr<pacman::BaseStatePickupOverlap> pacman::HasEatenStateSmallPickupOverlap::HandleOverlap()
{
	m_Timer = 0.0;

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
}

pacman::BaseStatePacman* pacman::CollectingState::Update(double, PacmanFSMComponent*)
{
	return nullptr;
}

pacman::BaseStatePacman* pacman::CollectingState::HandleOverlap(amu::CollisionComponent* otherColliderPtr, PacmanFSMComponent* ownerPtr)
{
	std::string_view otherTag{ otherColliderPtr->GetComponentOwner()->GetTag() };
	if (otherTag == tags::BLINKY)
	{
		return ownerPtr->GetState<DyingState>();
	}
	return nullptr;
}

void pacman::DyingState::OnEnter(PacmanFSMComponent*)
{
}

void pacman::DyingState::OnExit(PacmanFSMComponent*)
{
}

void pacman::DyingState::HandleInput(glm::vec2 const&, PacmanFSMComponent*)
{
}

pacman::BaseStatePacman* pacman::DyingState::Update(double, PacmanFSMComponent*)
{
	return nullptr;
}

pacman::BaseStatePacman* pacman::DyingState::HandleOverlap(amu::CollisionComponent*, PacmanFSMComponent*)
{
	return nullptr;
}
