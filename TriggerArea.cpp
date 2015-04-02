/*
 * TriggerArea.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: naiello
 */

#include "TriggerArea.h"

TriggerArea::TriggerArea(Uint32 id) :
	WorldObject(id)
{

}

void TriggerArea::linkOutput(string outpName, WorldOutput handler)
{
	if (outpName == "onTrigger")
		onTrigger = handler;
	else if (outpName == "onEnter")
		onEnter = handler;
	else if (outpName == "onLeave")
		onLeave = handler;
	else
		WorldObject::linkOutput(outpName, handler);
}

bool TriggerArea::canCollideWith(const WorldObject* other)
{
	return (other->getCollisionGroup() == COLGRP_PLAYER);
}

void TriggerArea::update(Uint32 time)
{
	if (!playerTouchedThisFrame && playerInside)
	{
		playerInside = false;
		if (onLeave)
			onLeave();
	}

	playerTouchedThisFrame = false;
}

void TriggerArea::handleCollision(WorldObject* other, const SDL_Rect& overlap)
{
	playerTouchedThisFrame = true;

	if (onTrigger)
		onTrigger();

	if (!playerInside)
	{
		playerInside = true;
		if (onEnter)
			onEnter();
	}
}
