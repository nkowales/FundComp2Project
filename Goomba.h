/*
 * Goomba.h
 *
 *  Created on: Apr 19, 2015
 *      Author: naiello
 */

#ifndef GOOMBA_H_
#define GOOMBA_H_

#include "Enemy.h"

#define GOOMBA_WALKSPEED 50
#define GOOMBA_HEALTH 10
#define GOOMBA_SIZE 16

class Goomba : public Enemy
{
public:
	Goomba(Uint32);

	void init(ContentManager*);
	void draw(SDL_Renderer*);

	void onWalkIntoWall(WorldObject*, const SDL_Rect&);

private:
	AnimatedTexture sprite;
};

#endif /* GOOMBA_H_ */
