#include "Header\TextureComponent.h"

#include "Header\Renderer.h"
#include "Header\ResourceManager.h"

void TextureComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_Transform.GetPosition().x, m_Transform.GetPosition().y);
	}
}


void TextureComponent::SetTexture(const std::string& fileName)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(fileName);

	//if (m_Texture == nullptr)
	//{
	//	throw FileNotFoundException{ fileName };
	//}
}
