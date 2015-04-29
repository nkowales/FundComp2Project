/*
 * BowserSpawn.cpp
 *
 *  Created on: Apr 29, 2015
 *      Author: naiello
 */

#include "BowserSpawn.h"
#include "ObjectLayer.h"
BowserSpawn::BowserSpawn(Uint32 id) : WorldObject(id)
{

}

WorldInput BowserSpawn::resolveInput(string inp)
{
	if (inp == "spawn")
	{
		return GET_INPUT_POINTER(&BowserSpawn::spawn);
	}
	else
		return WorldObject::resolveInput(inp);
}

void BowserSpawn::spawn(WorldObject* sender, string arg)
{
	Bowser* boss = new Bowser(WorldObject::getUniqueID());
	boss->setPosition(position);
	getParentLayer()->addObject(boss);
}
