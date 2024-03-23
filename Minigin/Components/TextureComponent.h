#pragma once
#include <memory>
#include <string>

#include "Base/Component.h"
#include "Wrappers/Texture2D.h"
#include "TransformComponent.h"

namespace amu
{

	class TextureComponent final : public Component
	{
	public:
		explicit TextureComponent(GameObject *  ownerObjectPtr, const std::string& fileName = "");
		virtual ~TextureComponent() override = default;
	
		TextureComponent(const TextureComponent&) = delete;
		TextureComponent& operator= (const TextureComponent&) = delete;
		TextureComponent(TextureComponent&&) = delete;
		TextureComponent& operator= (const TextureComponent&&) = delete;
	
		void Render() const override;

		void SetTexture(const std::string& fileName);
		void SetTexture(std::unique_ptr<Texture2D> textureUPtr);
	private:
		std::unique_ptr<amu::Texture2D> m_TextureUPtr = nullptr;

		TransformComponent* m_TransformPtr = nullptr;
	};

}