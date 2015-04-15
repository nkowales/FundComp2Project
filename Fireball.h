/*
 * Fireball.h
 *
 *  Created on: Apr 12, 2015
 *      Author: naiello
 */

#ifndef FIREBALL_H_
#define FIREBALL_H_

#include "WorldObject.h"

#define FIREBALL_MAX_BOUNCES 3
#define FIREBALL_HSPEED 250
#define FIREBALL_VSPEED 200
#define FIREBALL_SIZE 8
#define FIREBALL_GRAVITY 800

#define FIREBALL_FRMW 8
#define FIREBALL_FRMH 9
#define FIREBALL_NFRM 4
#define FIREBALL_SPC  3
#define FIREBALL_ANIMSPD 5

#define FIREBALL_SCALE 1.

class Fireball : public WorldObject
{
public:
	Fireball(Uint32);

	void init(ContentManager* content);
	void update(Uint32 time);
	void draw(SDL_Renderer*);
	bool canCollideWith(const WorldObject*);
	void handleCollision(WorldObject*, const SDL_Rect&);

	void kill();
	void reverseDirection();
private:
	AnimatedTexture sprite;
	int nBounces = 0;
};

#endif /* FIREBALL_H_ */
