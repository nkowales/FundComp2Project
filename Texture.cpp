/*
 * Texture.cpp
 *
 *  Created on: Mar 15, 2015
 *      Author: naiello
 */

#include "Texture.h"

Texture::Texture(SDL_Texture* img)
{
	image = img;
	SDL_QueryTexture(img, NULL, NULL, &width, &height);
}

Texture::~Texture() { }

void Texture::draw(SDL_Renderer* renderer, int x, int y, float xs, float ys)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = width * xs;
	dst.h = height * ys;

	SDL_RenderCopyEx(renderer, image, NULL, &dst, 0, NULL, (SDL_RendererFlip)flags);
}

void Texture::draw(SDL_Renderer* renderer, SDL_Rect* src, SDL_Rect* dst)
{
	SDL_RenderCopyEx(renderer, image, src, dst, 0, NULL, (SDL_RendererFlip)flags);
}

void Texture::getDimensions(int* w, int* h) const
{
	if (w)
		*w = width;
	if (h)
		*h = height;
}

SDL_Texture* Texture::getImage() const
{
	return image;
}

void Texture::setFlipH(bool flip)
{
	if (flip)
		flags |= SDL_FLIP_HORIZONTAL;
	else
		flags &= ~SDL_FLIP_HORIZONTAL;
}

void Texture::setFlipV(bool flip)
{
	if (flip)
		flags |= SDL_FLIP_VERTICAL;
	else
		flags &= ~SDL_FLIP_VERTICAL;
}

Uint32 Texture::getFlags()
{
	return flags;
}
