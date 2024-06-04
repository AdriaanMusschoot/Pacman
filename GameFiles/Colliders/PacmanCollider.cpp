#include "PacmanCollider.h"
#include "Configuration.h"
#include "ServiceLocator.h"
#include "GameTime.h"

pacman::PacmanCollider::PacmanCollider(amu::GameObject* ownerObjectPtr)
	: CollisionComponent(ownerObjectPtr, std::vector<std::string>{ pacman::tags::PICKUP_SMALL })
	, Subject(ownerObjectPtr)
	, m_StateSmallPickupUPtr{ std::make_unique<WaitingStateSmallPickupOverlap>() }
{
}

void pacman::PacmanCollider::Update()
{
	if (auto newState{ std::move(m_StateSmallPickupUPtr->Update(amu::GameTime::GetInstance().GetDeltaTime())) }; newState != nullptr)
	{
		m_StateSmallPickupUPtr->OnExit();
		m_StateSmallPickupUPtr = std::move(newState);
		m_StateSmallPickupUPtr->OnEnter();
	}
}

void pacman::PacmanCollider::OnCollision(amu::CollisionComponent* otherCollider)
{
	if (otherCollider->GetComponentOwner()->GetTag() == pacman::tags::PICKUP_SMALL)
	{
		if (auto newState{ std::move(m_StateSmallPickupUPtr->HandleOverlap()) }; newState != nullptr)
		{
			m_StateSmallPickupUPtr->OnExit();
			m_StateSmallPickupUPtr = std::move(newState);
			m_StateSmallPickupUPtr->OnEnter();
		}
	}
}

std::unique_ptr<pacman::BaseStateSmallPickupOverlap> pacman::WaitingStateSmallPickupOverlap::Update(double)
{
	return nullptr;
}

std::unique_ptr<pacman::BaseStateSmallPickupOverlap> pacman::WaitingStateSmallPickupOverlap::HandleOverlap()
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

std::unique_ptr<pacman::BaseStateSmallPickupOverlap> pacman::HasEatenStateSmallPickupOverlap::Update(double elapsedTime)
{
	m_Timer += elapsedTime;
	if (m_Timer >= m_MaxTime)
	{
		return std::make_unique<WaitingStateSmallPickupOverlap>();
	}
	return nullptr; 
}

std::unique_ptr<pacman::BaseStateSmallPickupOverlap> pacman::HasEatenStateSmallPickupOverlap::HandleOverlap() 
{
	m_Timer = 0.0;
	
	return nullptr;
}
