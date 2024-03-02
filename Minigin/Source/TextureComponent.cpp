#include "Header\TextureComponent.h"

#include "SDL_egl.h"
#include "Header\Renderer.h"
#include "Header\ResourceManager.h"
#include "Header\GameObject.h"

amu::TextureComponent::TextureComponent(const std::shared_ptr<GameObject>& ownerObjectSPtr)
	: Component(ownerObjectSPtr)
	, m_TransformPtr{ GetOwnerGameObject()->GetComponent<TransformComponent>() }

{
}

void amu::TextureComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		amu::Renderer::GetInstance().RenderTexture(*m_Texture, m_TransformPtr->GetWorldPosition().x, m_TransformPtr->GetWorldPosition().y);
	}
}

void amu::TextureComponent::SetTexture(const std::string& fileName)
{
	m_Texture = amu::ResourceManager::GetInstance().LoadTexture(fileName);
}

void amu::TextureComponent::SetTexture(const std::shared_ptr<Texture2D>& textureSPtr)
{
	m_Texture = textureSPtr;
}
