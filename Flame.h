/*
 * Flame.h
 *
 *  Created on: Apr 28, 2015
 *      Author: gnemecek
 *
 *      The flame that is on the floor of Bowser's castle level
 *      It can damage the player upon contact.
 */

#ifndef FLAME_H_
#define FLAME_H_

#include "Enemy.h"

class Flame : public Enemy
{
public:
	Flame(Uint32);

	void init(ContentManager*);
	void draw(SDL_Renderer*);

};

#endif /* FLAME_H_ */
