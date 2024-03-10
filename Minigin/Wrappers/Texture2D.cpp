#include <SDL.h>
#include "Wrappers/Texture2D.h"

amu::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

glm::ivec2 amu::Texture2D::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* amu::Texture2D::GetSDLTexture() const
{
	return m_texture;
}

amu::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_texture = texture;
}
