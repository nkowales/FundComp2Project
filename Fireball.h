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
#define FIREBALL_HSPEED 150
#define FIREBALL_SIZE 16

class Fireball : public WorldObject
{
public:
	Fireball(Uint32);

	void update(Uint32 time);
	void draw(SDL_Renderer*);
	bool canCollideWith(const WorldObject*);
	void handleCollision(WorldObject*, const SDL_Rect&);

	void kill();
	void reverseDirection();
private:
	int nBounces = 0;
};

#endif /* FIREBALL_H_ */
