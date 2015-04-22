/*
 * Hammer.h
 *
 *  Created on: Apr 21, 2015
 *      Author: mtroy2
 */

#ifndef HAMMER_H_
#define HAMMER_H_

#include "WorldObject.h"


#define HAMMER_HSPEED 170
#define HAMMER_VSPEED 170
#define HAMMER_SIZE 8
#define HAMMER_GRAVITY 200

#define HAMMER_FRMW 16
#define HAMMER_FRMH 16
#define HAMMER_NFRM 8
#define HAMMER_SPC  0
#define HAMMER_ANIMSPD 8

#define HAMMER_SCALE 1.

class Hammer : public WorldObject
{
public:
	Hammer(Uint32);
	void init(ContentManager* content);
	void update(Uint32 time);
	void draw(SDL_Renderer*);
	bool canCollideWith(const WorldObject*);
	void handleCollision(WorldObject*, const SDL_Rect&);
	void reverseDirection();
	void kill();
private:
	AnimatedTexture sprite;

};

#endif /* HAMMER_H_ */
