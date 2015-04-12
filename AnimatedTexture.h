/*
 * AnimatedTexture.h
 *
 *  Created on: Apr 12, 2015
 *      Author: naiello
 */

#ifndef ANIMATEDTEXTURE_H_
#define ANIMATEDTEXTURE_H_

#include "Texture.h"
#include "Geom.h"

class AnimatedTexture : public Texture
{
public:
	AnimatedTexture(SDL_Texture* = NULL, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);

	void draw(SDL_Renderer*, int, int, float = 1., float = 1.);

private:
	Vector2i offset;
	int frameWidth;
	int frameHeight;
	int spacing;
	int nFrames;
	int animSpeed;

	int currentFrame = 0;
	int ticksSinceLastShift = 0;

	void tick();
};

#endif /* ANIMATEDTEXTURE_H_ */
