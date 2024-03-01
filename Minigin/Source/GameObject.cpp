#include "Header\GameObject.h"

#include <algorithm>

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

void dae::GameObject::SetParent(GameObject* newParentObjectPtr, bool keepWorldPosition)
{
    if(IsChild(newParentObjectPtr) || newParentObjectPtr == this || m_ParentObjectPtr == newParentObjectPtr)
    {
        return;
    }
    if (m_ParentObjectPtr) m_ParentObjectPtr->RemoveChild(this);
    m_ParentObjectPtr = newParentObjectPtr;
    if (m_ParentObjectPtr) m_ParentObjectPtr->AddChild(this);
}

bool dae::GameObject::IsChild(const GameObject* gameObjectPtr) const
{
    return std::ranges::any_of(m_ChildObjectPtrVec,
    [&](const GameObject* objPtr)
    {
        return objPtr == gameObjectPtr;
    });
}

void dae::GameObject::RemoveChild(GameObject* gameObject)
{
    std::erase(m_ChildObjectPtrVec, gameObject);
}

void dae::GameObject::AddChild(GameObject* gameObjectPtr)
{
    m_ChildObjectPtrVec.emplace_back(gameObjectPtr);
}


