#include "Base/GameObject.h"

#include <algorithm>
#include "Components/TransformComponent.h"
#include "SDL_egl.h"

void amu::GameObject::Update()
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

void amu::GameObject::Render() const
{
    for(const auto & component: m_ComponentUPtrVec)
    {
        component->Render();
    }
}

void amu::GameObject::SetParent(GameObject* newParentObjectPtr, bool keepWorldPosition)
{
    if(IsChild(newParentObjectPtr) || newParentObjectPtr == this || m_ParentObjectPtr == newParentObjectPtr)
    {
        return;
    }

	TransformComponent* temp = GetComponent<TransformComponent>();
    if (newParentObjectPtr == nullptr)
    {
        temp->SetLocalPosition(temp->GetWorldPosition());
    }
    else
    {
	    if (keepWorldPosition)
	    {
            temp->SetLocalPosition(temp->GetWorldPosition() - newParentObjectPtr->GetComponent<TransformComponent>()->GetWorldPosition());
	    }
        else
        {
			temp->SetTransformDirty();
        }
    }

    if (m_ParentObjectPtr)
    {
        m_ParentObjectPtr->RemoveChild(this);
    }

    m_ParentObjectPtr = newParentObjectPtr;

    if (m_ParentObjectPtr)
    {
        m_ParentObjectPtr->AddChild(this);
    }
}

bool amu::GameObject::IsChild(const GameObject* parentObjectPtr) const
{
    return std::ranges::any_of(m_ChildObjectPtrVec,
    [&](const GameObject* childObjectPtr)
    {
    	return childObjectPtr->IsChild(parentObjectPtr);
    });
}

void amu::GameObject::RemoveChild(GameObject* gameObject)
{
    std::erase(m_ChildObjectPtrVec, gameObject);
}

void amu::GameObject::AddChild(GameObject* gameObjectPtr)
{
    m_ChildObjectPtrVec.emplace_back(gameObjectPtr);
}