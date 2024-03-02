#pragma once
#include <memory>
#include <string>

#include "Component.h"
#include "Texture2D.h"
#include "TransformComponent.h"

namespace amu
{

	class TextureComponent final : public Component
	{
	public:
		TextureComponent(const std::shared_ptr<GameObject>& ownerObjectSPtr);
		~TextureComponent() override = default;
	
		TextureComponent(const TextureComponent&) = delete;
		TextureComponent& operator= (const TextureComponent&) = delete;
		TextureComponent(TextureComponent&&) = delete;
		TextureComponent& operator= (const TextureComponent&&) = delete;
	
		void Render() const override;

		void SetTexture(const std::string& fileName);
		void SetTexture(const std::shared_ptr<Texture2D>& textureSPtr);
	private:
		std::shared_ptr<amu::Texture2D> m_Texture{ nullptr };

		TransformComponent* m_TransformPtr{ nullptr };
	};

}