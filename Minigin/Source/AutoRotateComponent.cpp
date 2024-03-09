#include "Header/AutoRotateComponent.h"

#include "Header/GameObject.h"
#include "Header/Time.h"

amu::AutoRotateComponent::AutoRotateComponent(GameObject * ownerObjectSPtr)
	: Component(ownerObjectSPtr)
	, m_TransformPtr{ GetOwnerGameObject()->GetComponent<TransformComponent>() }
{
	m_CenterPosition = m_TransformPtr->GetLocalPosition();
}

amu::AutoRotateComponent::AutoRotateComponent(amu::GameObject * ownerObjectSPtr, int radius, double speed, double angle)
	: AutoRotateComponent(ownerObjectSPtr)
{
	m_Radius = radius;
	m_Speed = speed;
	m_Angle = angle;
}

void amu::AutoRotateComponent::Update()
{
	m_Angle += m_Speed * Time::GetInstance().GetDeltaTime();

	const double x = m_CenterPosition.x + m_Radius * cos(m_Angle);
	const double y = m_CenterPosition.y + m_Radius * sin(m_Angle);

	m_TransformPtr->SetLocalPosition(glm::vec3{ x, y, 0 });
}
