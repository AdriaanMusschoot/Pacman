#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Singletons/ResourceManager.h"
#include "Singletons/Renderer.h"
#include "Wrappers/Texture2D.h"
#include "Wrappers/Font.h"

void amu::ResourceManager::Init(const std::filesystem::path& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::unique_ptr<amu::Texture2D> amu::ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_dataPath/file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.string().c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_unique<Texture2D>(texture);
}

std::unique_ptr<amu::Font> amu::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	const auto fullPath = m_dataPath/file;
	return std::make_unique<Font>(fullPath.string(), size);
}
