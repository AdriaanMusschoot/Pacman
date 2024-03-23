#pragma once
#include <memory>
#include <string>

#include "Base/Component.h"
#include "TextureComponent.h"
#include "Wrappers/Font.h"
#include "Wrappers/Texture2D.h"

namespace amu
{

	class TextComponent final : public Component
	{
	public:
		explicit TextComponent(GameObject * ownerObjectPtr, const std::string& textToDisplay, const std::string& fontPath, unsigned int size = 10);
		virtual ~TextComponent() override = default;
	
		TextComponent(const TextComponent&) = delete;
		TextComponent& operator= (const TextComponent&) = delete;
		TextComponent(TextComponent&&) = delete;
		TextComponent& operator= (const TextComponent&&) = delete;
	
		void Update() override;
		void Render() const override;
		
		void SetText(const std::string& textToDisplay);
	private:

		std::string m_Text{ "" };

		std::unique_ptr<amu::Font> m_FontUPtr{ nullptr };

		TransformComponent* m_TransformPtr{ nullptr };

		TextureComponent* m_TextureComponentPtr{ nullptr };

		bool m_NeedsUpdate{ true };
	};

}