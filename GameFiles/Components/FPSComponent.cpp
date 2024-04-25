#include "FPSComponent.h"

#include <sstream>

#include "GameObject.h"
#include "TextComponent.h"
#include "GameTime.h"

amu::FPSComponent::FPSComponent(amu::GameObject * ownerObjectPtr)
	: Component(ownerObjectPtr)
	, m_TextPtr{ GetComponentOwner()->GetComponent<TextComponent>() }
{
}

void amu::FPSComponent::Update()
{
	m_CurrentRefreshTime += GameTime::GetInstance().GetDeltaTime();
	m_TicksPassed++;
	if (m_CurrentRefreshTime < m_MaxRefreshTime)
	{
		return;
	}
	double currentFPS{ m_TicksPassed / m_CurrentRefreshTime };
	if (currentFPS != m_PreviousFPSCount)
	{
		if(m_TextPtr)
		{
			m_TextPtr->SetText(std::format("{:.1f}", currentFPS));
		}
		m_PreviousFPSCount = currentFPS;
	}
	m_CurrentRefreshTime = 0.0;
	m_TicksPassed = 0;
}
