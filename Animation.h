/*
 * Animation.h
 *
 *  Created on: Apr 15, 2015
 *      Author: naiello
 *
 *      Helper struct for AnimatedTexture.  AnimatedTextures are made up of a list of these animations.
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

struct Animation
{
	int srcOffsetX;
	int srcOffsetY;
	int frameWidth;
	int frameHeight;
	int spacing;
	int nFrames;
};

#endif /* ANIMATION_H_ */
