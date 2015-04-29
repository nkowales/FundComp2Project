/*
 * MushrooomSpawner.h
 *
 *  Created on: Apr 29, 2015
 *      Author: naiello
 */

#ifndef MUSHROOMSPAWNER_H_
#define MUSHROOMSPAWNER_H_

#include "WorldObject.h"
#include "HealthMushroom.h"

#define MSPAWN_SPEED 100

class MushroomSpawner : public WorldObject
{
public:
	MushroomSpawner(Uint32);

	void init(ContentManager*);
	void update(Uint32);
	bool canCollideWith(const WorldObject*);
	void handleCollision(WorldObject*, const SDL_Rect&);
	WorldInput resolveInput(string);

	void spawn();
	void enable(WorldObject* = NULL, string = "");

private:
	bool enabled = false;
	double timer = 0.;
	double spawnInterval = 15.;
};


#endif /* MUSHROOMSPAWNER_H_ */
