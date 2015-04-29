/*
 * BowserSpawn.h
 *
 *  Created on: Apr 29, 2015
 *      Author: naiello
 */

#ifndef BOWSERSPAWN_H_
#define BOWSERSPAWN_H_

#include "WorldObject.h"
#include "Bowser.h"

class BowserSpawn : public WorldObject
{
public:
	BowserSpawn(Uint32);
	WorldInput resolveInput(string);
	void spawn(WorldObject* = NULL, string = "");
};

#endif /* BOWSERSPAWN_H_ */
