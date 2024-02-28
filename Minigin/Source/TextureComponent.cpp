#include "Header\TextureComponent.h"

#include "Header\Renderer.h"
#include "Header\ResourceManager.h"

dae::TextureComponent::TextureComponent()
	: m_TransformUPtr{ std::make_unique<TransformComponent>() }
{
}

void dae::TextureComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_TransformUPtr->GetPosition().x, m_TransformUPtr->GetPosition().y);
	}
}

void dae::TextureComponent::SetPosition(float x, float y, float z)
{
	m_TransformUPtr->SetPosition(x, y, z);
}


void dae::TextureComponent::SetTexture(const std::string& fileName)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(fileName);
}
