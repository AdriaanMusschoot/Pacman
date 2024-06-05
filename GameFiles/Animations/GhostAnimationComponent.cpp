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
	m_Timer += amu::GameTime::GetInstance().GetDeltaTime();
	if (m_Timer >= m_MaxTime)
	{
		m_CurrentColIdx = ++m_CurrentColIdx % m_ColsPerDirection;
		m_Timer = 0.0;
		SDL_Rect const& oldSourceRect{ m_RenderComponentPtr->GetSourceRectangle() };
		m_RenderComponentPtr->SetSourceRectangle(SDL_Rect{ (m_CurrentColIdx + m_CurrentDirectionIdx) * oldSourceRect.w, 0, oldSourceRect.w, oldSourceRect.h });
	}
}

void pacman::GhostAnimationComponent::OnNotify(Event eventType, amu::Subject* subjectPtr)
{
	if (eventType == events::GRID_DIRECTION_CHANGES)
	{
		GridMovementComponent* gridMoveCompPtr{ subjectPtr->GetSubjectOwner()->GetComponent<GridMovementComponent>() };
		glm::vec2 const& currDir{ gridMoveCompPtr->GetCurrentDirection() };

		if (currDir == config::VEC_UP)
		{
			m_CurrentDirectionIdx = m_ColIdxUp;
		}
		else if (currDir == config::VEC_DOWN)
		{
			m_CurrentDirectionIdx = m_ColIdxDown;
		}
		else if (currDir == config::VEC_LEFT)
		{
			m_CurrentDirectionIdx = m_ColIdxLeft;
		}
		else if (currDir == config::VEC_RIGHT)
		{
			m_CurrentDirectionIdx = m_ColIdxRight;
		}
		SDL_Rect const& oldSourceRect{ m_RenderComponentPtr->GetSourceRectangle() };
		m_RenderComponentPtr->SetSourceRectangle(SDL_Rect{ (m_CurrentColIdx + m_CurrentDirectionIdx) * oldSourceRect.w, 0, oldSourceRect.w, oldSourceRect.h });
	}
}
