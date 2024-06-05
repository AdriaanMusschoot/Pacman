#include "PacmanCollider.h"
#include "Configuration.h"
#include "ServiceLocator.h"
#include "GameTime.h"

pacman::PacmanCollider::PacmanCollider(amu::GameObject* ownerObjectPtr)
	: CollisionComponent(ownerObjectPtr, std::vector<std::string>{ pacman::tags::PICKUP_SMALL })
	, Subject(ownerObjectPtr)
	, m_StatePickupUPtr{ std::make_unique<WaitingStateSmallPickupOverlap>() }
{
}

void pacman::PacmanCollider::Update()
{
	if (auto newState{ std::move(m_StatePickupUPtr->Update(amu::GameTime::GetInstance().GetDeltaTime())) }; newState != nullptr)
	{
		m_StatePickupUPtr->OnExit();
		m_StatePickupUPtr = std::move(newState);
		m_StatePickupUPtr->OnEnter();
	}
}

void pacman::PacmanCollider::OnCollision(amu::CollisionComponent* otherCollider)
{
	std::string_view otherTag{ otherCollider->GetComponentOwner()->GetTag() };
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
