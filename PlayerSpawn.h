/*
 * PlayerSpawn.h
 *
 *  Created on: Mar 28, 2015
 *      Author: naiello
 *
 *      WorldObject that generates a Player instance when initialized.
 */

#ifndef PLAYERSPAWN_H_
#define PLAYERSPAWN_H_

#include <iostream>
#include "WorldObject.h"
#include "ObjectLayer.h"
#include "Player.h"

using namespace std;

class PlayerSpawn : public WorldObject
{
public:
	PlayerSpawn(Uint32);

	void init();

	void setProperty(string, string);

private:
	bool spawnOnInit;
};

#endif /* PLAYERSPAWN_H_ */
