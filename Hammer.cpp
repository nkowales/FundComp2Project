/*
 * Hammer.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: mtroy2
 */

#include "Hammer.h"
#include "ObjectLayer.h"

Hammer::Hammer(Uint32 id) : WorldObject(id)
{
	SDL_Rect bbox = {0, 0, HAMMER_SIZE, HAMMER_SIZE};
	setBoundingBox(bbox);
	setCollisionGroup(COLGRP_ENEMPROJECTILE);
	velocity.x = HAMMER_HSPEED;
	velocity.y = HAMMER_VSPEED;
}

void Hammer::init(ContentManager* content)
{
	sprite = content->getAnimatedTexture("sprites/M-hammerkoopa.png", 333, 20, HAMMER_FRMW,
			HAMMER_FRMH, HAMMER_SPC, HAMMER_NFRM, HAMMER_ANIMSPD);
}

bool Hammer::canCollideWith(const WorldObject* other)
{
	Uint32 grp = other->getCollisionGroup();
	return ( (grp == COLGRP_WORLD)||(grp == COLGRP_PROJECTILE)||(grp == COLGRP_PLAYER) );

}

void Hammer::update(Uint32 time)
{
	if (delay > 0)
		return;
	double secs = time / 1000.;
	velocity.y += HAMMER_GRAVITY * secs;
	
	WorldObject::update(time);
}


void Hammer::handleCollision(WorldObject* other, const SDL_Rect& overlap)
{
	kill();
}

void Hammer::draw(SDL_Renderer* renderer)
{
	if (delay > 0 ){
		delay--;
		return;
	}
	SDL_Rect rect = getCamera()->transform(getBoundingBox());
	sprite.draw(renderer, rect.x, rect.y, HAMMER_SCALE, HAMMER_SCALE);
}

void Hammer::kill()
{
	getParentLayer()->removeObject(getId());
}
void Hammer::reverseDirection()
{
	velocity.x = -velocity.x;
}
int Hammer::getContactDamage()
{
	return contactDamage;
}
int Hammer::getXVel()
{
	return velocity.x;
}
