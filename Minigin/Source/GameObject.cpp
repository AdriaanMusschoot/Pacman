#include "Header\GameObject.h"

void dae::GameObject::Update()
{
    for (const auto& component : m_ComponentUPtrVec)
    {
        component->Update();
    }
    std::erase_if(m_ComponentUPtrVec,
        [&](const std::unique_ptr<Component>& componentUPtr)
        {
            return componentUPtr->GetToBeDestroyed();
        });
}

void dae::GameObject::Render() const
{
    for(const auto & component: m_ComponentUPtrVec)
    {
        component->Render();
    }
}