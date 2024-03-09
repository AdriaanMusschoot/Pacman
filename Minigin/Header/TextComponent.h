#pragma once
#include <memory>
#include <string>

#include "Component.h"
#include "TextureComponent.h"
#include "Font.h"
#include "Texture2D.h"

namespace amu
{

	class TextComponent final : public Component
	{
	public:
		TextComponent(GameObject * ownerObjectSPtr, const std::string& textToDisplay, const std::string& fontPath, unsigned int size = 10);
		~TextComponent() override = default;
	
		TextComponent(const TextComponent&) = delete;
		TextComponent& operator= (const TextComponent&) = delete;
		TextComponent(TextComponent&&) = delete;
		TextComponent& operator= (const TextComponent&&) = delete;
	
		void Update() override;
		void Render() const override;
		
		void SetText(const std::string& textToDisplay);
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<amu::Font> m_FontUPtr;

		TransformComponent* m_TransformPtr;

		std::unique_ptr<TextureComponent> m_TextureComponentUPtr;
	};

}