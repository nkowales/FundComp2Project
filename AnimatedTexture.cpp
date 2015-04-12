/*
 * AnimatedTexture.cpp
 *
 *  Created on: Apr 12, 2015
 *      Author: naiello
 */

#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(SDL_Texture* img, int xoffs, int yoffs, int frmw, int frmh, int spc, int frms, int rate)
	: Texture(img),
	  offset({xoffs, yoffs}),
	  spacing(spc),
	  nFrames(frms),
	  animSpeed(rate),
	  frameWidth(frmw),
	  frameHeight(frmh)
{

}

void AnimatedTexture::draw(SDL_Renderer* renderer, int x, int y, float xs, float ys)
{
	tick();
	SDL_Rect src;
	src.x = offset.x + (frameWidth + spacing) * currentFrame;
	src.y = offset.y;
	src.w = frameWidth;
	src.h = frameHeight;

	SDL_Rect dst = {x, y, (int)(frameWidth * xs), (int)(frameHeight * ys)};

	Texture::draw(renderer, &src, &dst);
}

void AnimatedTexture::tick()
{
	ticksSinceLastShift++;
	if (ticksSinceLastShift > animSpeed)
	{
		ticksSinceLastShift = 0;
		currentFrame++;

		if (currentFrame >= nFrames)
		{
				currentFrame = 0;
		}
	}
}
