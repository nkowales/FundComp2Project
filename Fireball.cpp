/*
 * Fireball.cpp
 *
 *  Created on: Apr 12, 2015
 *      Author: naiello
 */

#include "Fireball.h"
#include "ObjectLayer.h"

Fireball::Fireball(Uint32 id) : WorldObject(id)
{
	SDL_Rect bbox = {0, 0, FIREBALL_SIZE, FIREBALL_SIZE};
	setBoundingBox(bbox);
	setCollisionGroup(COLGRP_PROJECTILE);
	velocity.x = FIREBALL_HSPEED;
	velocity.y = FIREBALL_VSPEED;
}

void Fireball::init(ContentManager* content)
{
	sprite = content->getAnimatedTexture("sprites/fireball.png", 0, 0, FIREBALL_FRMW,
			FIREBALL_FRMH, FIREBALL_SPC, FIREBALL_NFRM, FIREBALL_ANIMSPD);
}

bool Fireball::canCollideWith(const WorldObject* other)
{
	return ((other->getCollisionGroup() == COLGRP_WORLD) || (other->getCollisionGroup() == COLGRP_ONEWAY));
}

void Fireball::update(Uint32 time)
{
	double secs = time / 1000.;
	velocity.y += FIREBALL_GRAVITY * secs;

	if (nBounces > FIREBALL_MAX_BOUNCES)
		kill();

	WorldObject::update(time);
}

void Fireball::reverseDirection()
{
	velocity.x = -velocity.x;
}

void Fireball::handleCollision(WorldObject* other, const SDL_Rect& overlap)
{
	if ((position.y + FIREBALL_SIZE / 2) < overlap.y)
	{
		velocity.y = -velocity.y;
		nBounces++;
	}
	else
	{
		kill();
	}
}

void Fireball::draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = getCamera()->transform(getBoundingBox());
	/*SDL_SetRenderDrawColor(renderer, 255, 128, 0, 255);
	SDL_Rect rect = getCamera()->transform(getBoundingBox());
	SDL_RenderDrawRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);*/

	sprite.draw(renderer, rect.x, rect.y, FIREBALL_SCALE, FIREBALL_SCALE);
}

void Fireball::kill()
{
	getParentLayer()->removeObject(getId());
}
