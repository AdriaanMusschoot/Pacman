#include <string>
#include "Header\GameObject.h"
#include "Header\ResourceManager.h"
#include "Header\Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
    for (const auto& component : m_ComponentUPtrVec)
    {
        component->Update();
    }
}

void dae::GameObject::Render() const
{
    for(const auto & component: m_ComponentUPtrVec)
    {
        component->Render();
    }
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
