/*
 * PlayerSpawn.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: naiello
 */

#include "PlayerSpawn.h"

PlayerSpawn::PlayerSpawn(Uint32 id)
	: WorldObject(id),
	  spawnOnInit(false)
{

}

void PlayerSpawn::init()
{
	if (spawnOnInit)
	{
		Player* plyr = new Player;
		plyr->setPosition(position);
		ObjectLayer* lyr = getParentLayer();
		lyr->addObject(plyr);
	}
}

void PlayerSpawn::setProperty(string key, string val)
{
	if (key == "autospawn")
		spawnOnInit = true;
}
