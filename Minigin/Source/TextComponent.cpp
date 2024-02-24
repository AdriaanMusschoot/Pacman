#include "Header/TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>

#include "Header/ResourceManager.h"
#include "Header/Renderer.h"


TextComponent::TextComponent(const std::string& textToDisplay, const std::string& fontPath, const unsigned size)
	: m_NeedsUpdate{ true }
	, m_Text{ textToDisplay }
	, m_FontUPtr{ dae::ResourceManager::GetInstance().LoadFont(fontPath, size) }
	, m_TextTextureSPtr{ nullptr }
{
}

void TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_FontUPtr->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTextureSPtr = std::make_unique<dae::Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::Render() const
{
	if (m_TextTextureSPtr != nullptr)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_TextTextureSPtr, m_Transform.GetPosition().x, m_Transform.GetPosition().y);
	}
}

void TextComponent::SetText(const std::string& textToDisplay)
{
	m_Text = textToDisplay;
	m_NeedsUpdate = true;
}
