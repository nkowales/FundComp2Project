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
	setCollisionGroup(COLGRP_PROJECTILE);
	velocity.x = HAMMER_HSPEED;
	velocity.y = HAMMER_VSPEED;
}

void Hammer::init(ContentManager* content)
{
	sprite = content->getAnimatedTexture("sprites/M-hammerkoopa.png", 164, 21, HAMMER_FRMW,
			HAMMER_FRMH, HAMMER_SPC, HAMMER_NFRM, HAMMER_ANIMSPD);
}

bool Hammer::canCollideWith(const WorldObject* other)
{
	return (other->getCollisionGroup() == COLGRP_PLAYER);
}

void Hammer::update(Uint32 time)
{
	double secs = time / 1000.;
	velocity.y += HAMMER_GRAVITY * secs;
	WorldObject::update(time);
}


void Hammer::handleCollision(WorldObject* other, const SDL_Rect& overlap)
{
	cout << "collision detected in hammer";
	kill();
}

void Hammer::draw(SDL_Renderer* renderer)
{
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
