#include "Header\TextureComponent.h"

#include "Header\Renderer.h"
#include "Header\ResourceManager.h"
#include "Header\GameObject.h"
dae::TextureComponent::TextureComponent(const std::shared_ptr<GameObject>& parentObjectSPtr)
	: Component(parentObjectSPtr)
	, m_TransformPtr{ parentObjectSPtr->GetComponent<TransformComponent>() }

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
