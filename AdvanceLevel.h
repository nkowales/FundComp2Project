/*
 * AdvanceLevel.h
 *
 *  Created on: April 28, 2015
 *      Author: gnemecek
 *
 *      Invisible block that the player can collide with, upon which the user advances to the next level
 *      (will be around the treasure chest)
 */

#ifndef ADVANCELEVEL_H_
#define ADVANCELEVEL_H_

#include <iostream>
#include <SDL2/SDL.h>
#include "WorldObject.h"
#include "ObjectLayer.h"
#include "Player.h"

using namespace std;

class AdvanceLevel : public WorldObject
{
public:
	AdvanceLevel(Uint32);

	virtual WorldInput resolveInput(string);
	void loadMap(WorldObject*, string);
};

#endif 
