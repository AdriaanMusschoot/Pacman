#include "GhostAnimationComponent.h"
#include "GameObject.h"
#include "Components/GridMovementComponent.h"
#include "GameTime.h"

pacman::GhostAnimationComponent::GhostAnimationComponent(amu::GameObject* ownerObjectPtr)
	: Component(ownerObjectPtr)
{
	m_RenderComponentPtr = GetComponentOwner()->GetComponent<amu::RenderComponent>();
}

void pacman::GhostAnimationComponent::Update()
{
	double deltaTime = amu::GameTime::GetInstance().GetDeltaTime();
	m_Timer += deltaTime;
	if (m_Afraid)
	{
		m_TimerFlicker += deltaTime;
		if (m_TimerFlicker >= m_MaxTimeFlicker)
		{
			m_TimerFlicker = 0.0;
			m_MaxTimeFlicker -= m_DecreaseValueFlicker;
			if (m_CurrentOffsetIdx == m_ColAfraid1)
			{
				m_CurrentOffsetIdx = m_ColAfraid2;
			}
			else if (m_CurrentOffsetIdx == m_ColAfraid2)
			{
				m_CurrentOffsetIdx = m_ColAfraid1;
			}
		}
	}
	if (m_Timer >= m_MaxTime)
	{
		m_CurrentColIdx = ++m_CurrentColIdx % m_ColsPerDirection;
		m_Timer = 0.0;
	}
	SDL_Rect const& oldSourceRect{ m_RenderComponentPtr->GetSourceRectangle() };
	m_RenderComponentPtr->SetSourceRectangle(SDL_Rect{ (m_CurrentColIdx + m_CurrentOffsetIdx) * oldSourceRect.w, 0, oldSourceRect.w, oldSourceRect.h });
}

void pacman::GhostAnimationComponent::OnNotify(Event eventType, amu::Subject* subjectPtr)
{
	if (eventType == events::GRID_DIRECTION_CHANGES || eventType == events::GHOST_ATTACK)
	{
		GridMovementComponent* gridMoveCompPtr{ subjectPtr->GetSubjectOwner()->GetComponent<GridMovementComponent>() };
		glm::vec2 const& currDir{ gridMoveCompPtr->GetCurrentDirection() };

		if (currDir == config::VEC_UP)
		{
			m_CurrentOffsetIdx = m_ColIdxUp;
		}
		else if (currDir == config::VEC_DOWN)
		{
			m_CurrentOffsetIdx = m_ColIdxDown;
		}
		else if (currDir == config::VEC_LEFT)
		{
			m_CurrentOffsetIdx = m_ColIdxLeft;
		}
		else if (currDir == config::VEC_RIGHT)
		{
			m_CurrentOffsetIdx = m_ColIdxRight;
		}

		m_Afraid = false;
	}
	else if (eventType == events::GHOST_PANICK)
	{
		m_Afraid = true;
		m_TimerFlicker = 0.0;
		m_MaxTimeFlicker = m_StartValueFlicker;
		m_CurrentOffsetIdx = m_ColAfraid1;
	}
	else if (eventType == events::GHOST_RUSHING_TO_SPAWN)
	{
		m_Afraid = false;
		m_Returning = true;
		m_CurrentOffsetIdx = m_ColReturn;
	}
	SDL_Rect const& oldSourceRect{ m_RenderComponentPtr->GetSourceRectangle() };
	m_RenderComponentPtr->SetSourceRectangle(SDL_Rect{ (m_CurrentColIdx + m_CurrentOffsetIdx) * oldSourceRect.w, 0, oldSourceRect.w, oldSourceRect.h });
	
}
