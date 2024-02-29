#include "Header\TextureComponent.h"

#include "SDL_egl.h"
#include "Header\Renderer.h"
#include "Header\ResourceManager.h"
#include "Header\GameObject.h"

dae::TextureComponent::TextureComponent(const std::shared_ptr<GameObject>& parentObjectSPtr)
	: Component(parentObjectSPtr)
	, m_TransformPtr{ GetParentGameObject()->GetComponent<TransformComponent>() }

{
}

void dae::TextureComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_TransformPtr->GetPosition().x, m_TransformPtr->GetPosition().y);
	}
}

void dae::TextureComponent::SetTexture(const std::string& fileName)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(fileName);
}

void dae::TextureComponent::SetTexture(const std::shared_ptr<Texture2D>& textureSPtr)
{
	m_Texture = textureSPtr;
}
