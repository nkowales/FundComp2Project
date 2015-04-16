/*
 * AnimatedTexture.cpp
 *
 *  Created on: Apr 12, 2015
 *      Author: naiello
 */

#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(SDL_Texture* img, int xoffs, int yoffs, int frmw, int frmh, int spc, int frms, int rate)
	: Texture(img),
	  animSpeed(rate)
{
	addAnimation("default", xoffs, yoffs, frmw, frmh, spc, frms);
	setAnimation("default");
}

void AnimatedTexture::draw(SDL_Renderer* renderer, int x, int y, float xs, float ys)
{
	if (currentAnimation)
	{
		tick();
		SDL_Rect src;
		src.x = currentAnimation->srcOffsetX + (currentAnimation->frameWidth + currentAnimation->spacing) * currentFrame;
		src.y = currentAnimation->srcOffsetY;
		src.w = currentAnimation->frameWidth;
		src.h = currentAnimation->frameHeight;

		SDL_Rect dst = {x, y, (int)(currentAnimation->frameWidth * xs), (int)(currentAnimation->frameHeight * ys)};

		Texture::draw(renderer, &src, &dst);
	}
}

void AnimatedTexture::tick()
{
	if (!paused)
	{
		ticksSinceLastShift++;
		if (ticksSinceLastShift > animSpeed)
		{
			ticksSinceLastShift = 0;
			currentFrame++;

			if (currentFrame >= currentAnimation->nFrames)
			{
					if (animName == "ranged" | animName == "melee")
					{
						looping = false;
					} 
					else
					{ 
						looping = true;
					}
					currentFrame = 0;
					if (!looping)
					{
						setAnimation("default");
					}
			}
		}
	}
}

void AnimatedTexture::setLooping(bool loop)
{
	looping = loop;
}

void AnimatedTexture::pause()
{
	paused = true;
}

void AnimatedTexture::play()
{
	paused = false;
}

void AnimatedTexture::setAnimation(string anim)
{
	AnimList::iterator iter = animations.find(anim);
	animName = anim;
	if (iter != animations.end())
		currentAnimation = &(iter->second);
	else
		currentAnimation = NULL;

	currentFrame = 0;
}
string AnimatedTexture::getAnimation(){
	return animName;

}
void AnimatedTexture::addAnimation(string nm, int xoffs, int yoffs, int frmw, int frmh, int spc, int frms)
{
	Animation anim = {xoffs, yoffs, frmw, frmh, spc, frms};
	pair<string, Animation> pr(nm, anim);
	animations.insert(pr);
}
