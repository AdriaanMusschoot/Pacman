#include "Header\GameObject.h"

#include <algorithm>

#include "SDL_egl.h"

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

    if (newParentObjectPtr == nullptr)
    {
        SetLocalPosition(GetWorldPosition());
    }
    else
    {
	    if (keepWorldPosition)
	    {
            SetLocalPosition(GetWorldPosition() - newParentObjectPtr->GetWorldPosition());
	    }
        m_TransformDirty = true;
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

glm::vec3 dae::GameObject::GetWorldPosition() const
{
    if (m_TransformDirty)
    {
    	const_cast<GameObject*>(this)->UpdateWorldPosition();
    }
    return GetComponent<TransformComponent>()->GetWorldPosition();
}

glm::vec3 dae::GameObject::GetLocalPosition() const
{
    return GetComponent<TransformComponent>()->GetLocalPosition();
}

void dae::GameObject::SetLocalPosition(const glm::vec3& newPosition)
{
	GetComponent<TransformComponent>()->SetLocalPosition(newPosition);
    
    m_TransformDirty = true;
}

void dae::GameObject::UpdateWorldPosition()
{
    if (m_ParentObjectPtr == nullptr)
    {
        GetComponent<TransformComponent>()->SetWorldPosition(GetComponent<TransformComponent>()->GetLocalPosition());
    }
    else
    {
        GetComponent<TransformComponent>()->SetWorldPosition
        (
            m_ParentObjectPtr->GetComponent<TransformComponent>()->GetWorldPosition()
            +
            GetComponent<TransformComponent>()->GetLocalPosition()
        );
    }
    m_TransformDirty = false;
}


