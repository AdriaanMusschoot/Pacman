#include "Header/AutoRotateComponent.h"

#include "Header/GameObject.h"
#include "Header/Time.h"

amu::AutoRotateComponent::AutoRotateComponent(const std::shared_ptr<GameObject>& ownerObjectSPtr)
	: Component(ownerObjectSPtr)
	, m_TransformPtr{ GetOwnerGameObject()->GetComponent<TransformComponent>() }
{
	m_CenterPosition = m_TransformPtr->GetLocalPosition();
	if (const auto & parentPtr{ GetOwnerGameObject()->GetParent() }; parentPtr != nullptr)
	{
		m_ParentTransformPtr = parentPtr->GetComponent<TransformComponent>();
	}
}

amu::AutoRotateComponent::AutoRotateComponent(const std::shared_ptr<amu::GameObject>& ownerObjectSPtr, int radius,	double speed)
	: AutoRotateComponent(ownerObjectSPtr)
{
	m_Radius = radius;
	m_Speed = speed;
}

void amu::AutoRotateComponent::Update()
{
	m_Angle += m_Speed * Time::GetInstance().GetDeltaTime();

	//if (m_ParentTransformPtr != nullptr)
	//{
	//	m_CenterPosition = m_ParentTransformPtr->GetWorldPosition();
	//}

	const double x = m_CenterPosition.x + m_Radius * cos(m_Angle);
	const double y = m_CenterPosition.y + m_Radius * sin(m_Angle);

	m_TransformPtr->SetLocalPosition(glm::vec3{ x, y, 0 });
}
