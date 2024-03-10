#include "Components/AutoRotateComponent.h"

#include "Base/GameObject.h"
#include "Singletons/Time.h"

amu::AutoRotateComponent::AutoRotateComponent(GameObject * ownerObjectPtr)
	: Component(ownerObjectPtr)
	, m_TransformPtr{ GetOwnerGameObject()->GetComponent<TransformComponent>() }
{
	m_CenterPosition = m_TransformPtr->GetLocalPosition();
}

amu::AutoRotateComponent::AutoRotateComponent(amu::GameObject * ownerObjectPtr, int radius, double speed, double angle)
	: AutoRotateComponent(ownerObjectPtr)
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
