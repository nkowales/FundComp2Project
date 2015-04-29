/*
 * HealthMushroom.h
 *
 *  Created on: Apr 29, 2015
 *      Author: naiello
 *
 *      Provides additional health to the user upon collision.
 *      Helps the player to heal from the previous attacks by enemies.
 */

#ifndef HEALTHMUSHROOM_H_
#define HEALTHMUSHROOM_H_

#include "WorldObject.h"

class HealthMushroom : public WorldObject
{
public:
	HealthMushroom(Uint32);

	void init(ContentManager*);
	void draw(SDL_Renderer*);

private:
	AnimatedTexture tex;
};
#endif /* HEALTHMUSHROOM_H_ */
