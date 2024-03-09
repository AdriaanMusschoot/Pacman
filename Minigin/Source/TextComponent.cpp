#include "Header/TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>

#include "Header/ResourceManager.h"
#include "Header/Renderer.h"
#include "Header/GameObject.h"

amu::TextComponent::TextComponent(GameObject * ownerObjectPtr, const std::string& textToDisplay, const std::string& fontPath, const unsigned size)
	: Component(ownerObjectPtr)
	, m_Text{ textToDisplay }
	, m_FontUPtr{ amu::ResourceManager::GetInstance().LoadFont(fontPath, size) }
	, m_TransformPtr{ GetOwnerGameObject()->GetComponent<TransformComponent>() }
	, m_TextureComponentUPtr{ std::make_unique<TextureComponent>(ownerObjectPtr) }
{
}

void amu::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_FontUPtr->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(amu::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextureComponentUPtr->SetTexture(std::make_unique<Texture2D>(texture));
		m_NeedsUpdate = false;
	}
}

void amu::TextComponent::Render() const
{
	m_TextureComponentUPtr->Render();
}

void amu::TextComponent::SetText(const std::string& textToDisplay)
{
	m_Text = textToDisplay;
	m_NeedsUpdate = true;
}
