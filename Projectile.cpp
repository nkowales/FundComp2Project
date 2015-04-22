/*
 * Projectile.cpp
 *
 *  Created on: Apr 23, 2015
 *      Author: mtroy
 */

#include "Projectile.h"
#include "ObjectLayer.h"
#include "Enemy.h"
Projectile::Projectile(Uint32 id) : WorldObject(id)
{
	setCollisionGroup(COLGRP_PROJECTILE);
}

void Projectile::init(ContentManager* content)
{
}

bool Projectile::canCollideWith(const WorldObject* other)
{
	Uint32 grp = other->getCollisionGroup();
	return ( (grp == COLGRP_WORLD)||(grp == COLGRP_ONEWAY)||(grp == COLGRP_ENEMY) );
}

void Projectile::update(Uint32 time)
{
	
}

void Projectile::reverseDirection()
{
	velocity.x = -velocity.x;
}

void Projectile::handleCollision(WorldObject* other, const SDL_Rect& overlap)
{

	
}

void Projectile::draw(SDL_Renderer* renderer)
{
}


void Projectile::kill()
{
	getParentLayer()->removeObject(getId());
}
