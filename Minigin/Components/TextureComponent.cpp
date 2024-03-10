#include "Components/TextureComponent.h"

#include "SDL_egl.h"
#include "Singletons/Renderer.h"
#include "Singletons/ResourceManager.h"
#include "Base/GameObject.h"

amu::TextureComponent::TextureComponent(GameObject* ownerObjectPtr)
	: Component(ownerObjectPtr)
	, m_TransformPtr{ GetOwnerGameObject()->GetComponent<TransformComponent>() }
{
}

void amu::TextureComponent::Render() const
{
	if (m_TextureUPtr != nullptr)
	{
		amu::Renderer::GetInstance().RenderTexture(*m_TextureUPtr, m_TransformPtr->GetWorldPosition().x, m_TransformPtr->GetWorldPosition().y);
	}
}

void amu::TextureComponent::SetTexture(const std::string& fileName)
{
	m_TextureUPtr = amu::ResourceManager::GetInstance().LoadTexture(fileName);
}

void amu::TextureComponent::SetTexture(std::unique_ptr<Texture2D> textureUPtr)
{
	m_TextureUPtr = std::move(textureUPtr);
}