/*
*	AdvanceLevel.cpp
*	Created on April 28
*	Author : gnemecek
*
*
*/

#include "AdvanceLevel.h"
#include "WorldMap.h"
#include "ObjectLayer.h"
#include "ScreenManager.h"

AdvanceLevel::AdvanceLevel(Uint32 id) : WorldObject(id)
{

	//setCollisionGroup(COLGRP_ENEMBOUND);
}

WorldInput AdvanceLevel::resolveInput(string inp)
{
	if (inp == "load")
		return GET_INPUT_POINTER(&AdvanceLevel::loadMap);
	else
		return WorldObject::resolveInput(inp);
}

void AdvanceLevel::loadMap(WorldObject* sender, string map)
{
	ScreenManager* manager = getParentLayer()->getParent()->getManager();
	WorldMap* nmap = new WorldMap(map, manager->getRenderer());
	manager->addScreen(nmap);
	manager->removeScreen(getParentLayer()->getParent());
}
