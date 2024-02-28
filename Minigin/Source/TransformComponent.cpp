#include "Header/GameObject.h"
#include "Header/TransformComponent.h"

dae::TransformComponent::TransformComponent()
	: m_position{ 0, 0, 0 }
{

}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}