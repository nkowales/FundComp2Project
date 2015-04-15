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
#include "Animation.h"
#include <map>
#include <iostream>

using namespace std;

typedef map<string, Animation> AnimList;

class AnimatedTexture : public Texture
{
public:
	AnimatedTexture(SDL_Texture* = NULL, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);

	void draw(SDL_Renderer*, int, int, float = 1., float = 1.);
	void setLooping(bool);
	void play();
	void pause();

	void addAnimation(string, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
	void setAnimation(string);

private:
	AnimList animations;
	Animation* currentAnimation = NULL;
	bool looping = true;
	bool paused = false;
	int animSpeed = 5;
	int currentFrame = 0;
	int ticksSinceLastShift = 0;

	void tick();
};

#endif /* ANIMATEDTEXTURE_H_ */
