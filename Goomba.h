/*
 * Goomba.h
 *
 *  Created on: Apr 19, 2015
 *      Author: naiello
 *
 *      Basic enemy called Goomba.  It can walk around, but possesses no attacks.
 */

#ifndef GOOMBA_H_
#define GOOMBA_H_

#include "Enemy.h"

#define GOOMBA_WALKSPEED 50
#define GOOMBA_HEALTH 5
#define GOOMBA_SIZE 16
#define GOOMBA_STUNTIME 0.5

class Goomba : public Enemy
{
public:
	Goomba(Uint32);

	void init(ContentManager*);
	void draw(SDL_Renderer*);
	void squish();
	void onWalkIntoWall(WorldObject*, const SDL_Rect&);
	void stun();
	void update(Uint32);

private:
	AnimatedTexture sprite;
	bool walkingLeft = true;
};

#endif /* GOOMBA_H_ */
