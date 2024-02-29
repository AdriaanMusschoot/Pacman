#include "Header/FPSComponent.h"

#include <sstream>

#include "Header/GameObject.h"
#include "Header/TextComponent.h"
#include "Header/Time.h"

dae::FPSComponent::FPSComponent(const std::shared_ptr<dae::GameObject>& gameObjectSPtr)
	: Component(gameObjectSPtr)
{
}

void dae::FPSComponent::Update()
{
	m_CurrentRefreshTime += Time::GetInstance().GetDeltaTime();
	m_TicksPassed++;
	if (m_CurrentRefreshTime < m_MaxRefreshTime)
	{
		return;
	}
	if(const auto gameObject = GetParentGameObject().lock())
	{
		if (gameObject->ComponentAdded<TextComponent>())
		{
			std::stringstream tempSS;
			tempSS << std::fixed << std::setprecision(1) << m_TicksPassed / m_CurrentRefreshTime;
			m_FPSCountToDisplay = tempSS.str();
			gameObject->GetComponent<TextComponent>()->SetText(m_FPSCountToDisplay);
		}
	}
	m_CurrentRefreshTime = 0.0;
	m_TicksPassed = 0;
}
