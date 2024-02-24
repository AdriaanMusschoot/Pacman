#pragma once
#include <memory>
#include <string>

#include "Component.h"

namespace dae
{
	class Texture2D;
}

class TextureComponent final : public Component
{
public:
	TextureComponent() = default;
	~TextureComponent() override = default;

	TextureComponent(const TextureComponent&) = delete;
	TextureComponent& operator= (const TextureComponent&) = delete;
	TextureComponent(TextureComponent&&) = delete;
	TextureComponent& operator= (const TextureComponent&&) = delete;

	void Render() const override;

	void SetTexture(const std::string& fileName);
private:
	std::shared_ptr<dae::Texture2D> m_Texture{};
};
//ASK TOM IF THIS IS HOW YOU WOULD THEN THROW THE ERROR
//class FileNotFoundException : public std::exception
//{
//public:
//	FileNotFoundException(const std::string& fileName)
//		: m_FileName{ fileName }
//	{}
//	std::string GetExceptionMessage()
//	{
//		return m_FileName + " was not found";
//	}
//private:
//	std::string m_FileName;
//};