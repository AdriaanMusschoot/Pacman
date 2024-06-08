#include "PacmanAnimationComponent.h"
#include "GameObject.h"
#include "Components/GridMovementComponent.h"
#include "GameTime.h"

pacman::PacmanAnimationComponent::PacmanAnimationComponent(amu::GameObject* ownerObjectPtr)
	: Component(ownerObjectPtr)
	, Subject(ownerObjectPtr)
{
	m_RenderComponentPtr = GetComponentOwner()->GetComponent<amu::RenderComponent>();
}

void pacman::PacmanAnimationComponent::Update()
{
	if (m_Stuck)
	{
		return;
	}

	m_Timer += amu::GameTime::GetInstance().GetDeltaTime();

	if (m_Timer >= m_MaxTime)
	{
		if (m_Dying)
		{
			++m_CurrentColIdx;
			if (m_CurrentColIdx >= 14)
			{
				NotifyObservers(events::PACMAN_DYING_ANIM_FINISHED);
				m_CurrentColIdx = 2;
				m_Dying = false;
				m_Stuck = true;
			}
		}
		else
		{
			m_CurrentColIdx = ++m_CurrentColIdx % m_ColsPerAnimation;
		}
		m_Timer = 0.0;
		SDL_Rect const& oldSourceRect{ m_RenderComponentPtr->GetSourceRectangle() };
		m_RenderComponentPtr->SetSourceRectangle(SDL_Rect{ m_CurrentColIdx * oldSourceRect.w, m_CurrentRowIdx * oldSourceRect.h, oldSourceRect.w, oldSourceRect.h });
	}
}

void pacman::PacmanAnimationComponent::OnNotify(Event eventType, amu::Subject* subjectPtr)
{
	if (eventType == events::GRID_DIRECTION_CHANGES)
	{
		GridMovementComponent* gridMoveCompPtr{ subjectPtr->GetSubjectOwner()->GetComponent<GridMovementComponent>() };
		glm::vec2 const& currDir{ gridMoveCompPtr->GetCurrentDirection() };

		if (currDir == config::VEC_UP)
		{
			m_CurrentRowIdx = m_RowIdxUp;
			m_Stuck = false;
		}
		else if (currDir == config::VEC_DOWN)
		{
			m_CurrentRowIdx = m_RowIdxDown;
			m_Stuck = false;
		}
		else if (currDir == config::VEC_LEFT)
		{
			m_CurrentRowIdx = m_RowIdxLeft;
			m_Stuck = false;
		}
		else if (currDir == config::VEC_RIGHT)
		{
			m_CurrentRowIdx = m_RowIdxRight;
			m_Stuck = false;
		}
		else if (currDir == config::VEC_NEUTRAL)
		{
			if (not m_Dying)
			{
				m_Stuck = true;
			}
		}
		SDL_Rect const& oldSourceRect{ m_RenderComponentPtr->GetSourceRectangle() };
		m_RenderComponentPtr->SetSourceRectangle(SDL_Rect{ m_CurrentColIdx * oldSourceRect.w, m_CurrentRowIdx * oldSourceRect.h, oldSourceRect.w, oldSourceRect.h });
	}
	if (eventType == events::PACMAN_HIT_GHOST)
	{
		m_Dying = true;
		m_Stuck = false;
		m_CurrentRowIdx = 0;
		m_CurrentColIdx = 3;
	}
}
