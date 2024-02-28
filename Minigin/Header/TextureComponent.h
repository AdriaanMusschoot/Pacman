#pragma once
#include <memory>
#include <string>

#include "Component.h"
#include "Texture2D.h"
#include "TransformComponent.h"

namespace dae
{

	class TextureComponent final : public Component
	{
	public:
		TextureComponent();
		~TextureComponent() override = default;
	
		TextureComponent(const TextureComponent&) = delete;
		TextureComponent& operator= (const TextureComponent&) = delete;
		TextureComponent(TextureComponent&&) = delete;
		TextureComponent& operator= (const TextureComponent&&) = delete;
	
		void Render() const override;

		void SetPosition(float x, float y, float z = 0);

		void SetTexture(const std::string& fileName);
	private:
		std::unique_ptr<dae::TransformComponent> m_TransformUPtr;
		std::shared_ptr<dae::Texture2D> m_Texture{};
	};

}