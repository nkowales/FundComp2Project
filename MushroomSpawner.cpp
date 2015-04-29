/*
 * MushroomSpawner.cpp
 *
 *  Created on: Apr 29, 2015
 *      Author: naiello
 */

#include "MushroomSpawner.h"
#include "ObjectLayer.h"

MushroomSpawner::MushroomSpawner(Uint32 id)
	: WorldObject(id)
{

}

void MushroomSpawner::init(ContentManager* content)
{
	setBoundingBox({0, 0, 16, 4});
	setCollisionGroup(COLGRP_NONE);
}

void MushroomSpawner::update(Uint32 time)
{
	if (!enabled)
		return;

	double secs = time / 1000.;
	timer += secs;

	if (timer >= spawnInterval)
	{
		timer = 0.;
		spawn();
	}

	WorldObject::update(time);
}

bool MushroomSpawner::canCollideWith(const WorldObject* other)
{
	return (other->getCollisionGroup() == COLGRP_WORLD);
}

void MushroomSpawner::handleCollision( WorldObject* other, const SDL_Rect& overlap)
{
	velocity.x = -velocity.x;
	position.x += (velocity.x > 0) ? 2 : -2;
}

WorldInput MushroomSpawner::resolveInput(string inp)
{
	if (inp == "enable")
		return GET_INPUT_POINTER(&MushroomSpawner::enable);
	else
		return WorldObject::resolveInput(inp);
}

void MushroomSpawner::spawn()
{
	HealthMushroom* health = new HealthMushroom(WorldObject::getUniqueID());
	health->setPosition(position);
	getParentLayer()->addObject(health);
}

void MushroomSpawner::enable(WorldObject* sender,string arg)
{
	enabled = true;
	velocity.x = MSPAWN_SPEED;
}
