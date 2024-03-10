#include <stdexcept>
#include <cstring>
#include "Singletons/Renderer.h"
#include "Singletons/SceneManager.h"
#include "Wrappers/Texture2D.h"
#include "Singletons/GUI.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void amu::Renderer::Init(SDL_Window* window)
{
	m_WindowPtr = window;
	m_RendererPtr = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_RendererPtr == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	SDL_RenderSetVSync(m_RendererPtr, true);
}

void amu::Renderer::Render() const
{

	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_RendererPtr, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_RendererPtr);

	SceneManager::GetInstance().Render();

	GUI::GetInstance().EndFrame();

	SDL_RenderPresent(m_RendererPtr);
}

void amu::Renderer::Destroy()
{
	if (m_RendererPtr != nullptr)
	{
		SDL_DestroyRenderer(m_RendererPtr);
		m_RendererPtr = nullptr;
	}
}

void amu::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void amu::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

SDL_Renderer* amu::Renderer::GetSDLRenderer() const { return m_RendererPtr; }
