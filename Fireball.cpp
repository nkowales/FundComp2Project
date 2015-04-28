/*
 * Fireball.cpp
 *
 *  Created on: Apr 12, 2015
 *      Author: naiello
 */

#include "Fireball.h"
#include "ObjectLayer.h"
#include "Enemy.h"
Fireball::Fireball(Uint32 id) : Projectile(id)
{
	
	setCollisionGroup(COLGRP_PROJECTILE);
	velocity.x = 250;
	velocity.y = 200;
	maxBounces = 3;
	hSpeed = 250;
	vSpeed = 200;
	size = 8;
	gravity = 800;
	damage = 5;
	SDL_Rect bbox = {0, 0, size, size};
	setBoundingBox(bbox);

}

void Fireball::init(ContentManager* content)
{
	sprite = content->getAnimatedTexture("sprites/M-fireball.png", 0, 0, FIREBALL_FRMW,
			FIREBALL_FRMH, FIREBALL_SPC, FIREBALL_NFRM, FIREBALL_ANIMSPD);
}

bool Fireball::canCollideWith(const WorldObject* other)
{
	Uint32 grp = other->getCollisionGroup();
	return ( (grp == COLGRP_WORLD)||(grp == COLGRP_ONEWAY)||(grp == COLGRP_ENEMY) );
}

void Fireball::update(Uint32 time)
{
	double secs = time / 1000.;
	velocity.y += gravity * secs;

	if (nBounces > maxBounces)
		kill();

	WorldObject::update(time);
}

void Fireball::reverseDirection()
{
	velocity.x = -velocity.x;
}

void Fireball::handleCollision(WorldObject* other, const SDL_Rect& overlap)
{
	Uint32 grp = other->getCollisionGroup();
	Enemy* enemy;
	switch (grp)
	{
	case COLGRP_WORLD:
		if ((position.y + 2) < overlap.y)
		{
			velocity.y = -velocity.y;
			position.y = other->getPosition().y - size - 1;
			nBounces++;
		}
		break;
	case COLGRP_ONEWAY:
		if ((position.y + 2) < overlap.y)
		{
			velocity.y = -velocity.y;
			position.y = other->getPosition().y - size - 1;
			nBounces++;
		}
		break;
	case COLGRP_ENEMY:
		enemy = static_cast<Enemy*>(other);
		if (enemy->getInvuln() == true){
		} else {
			enemy->hurt(damage);
			kill();
		}
		break;
	}

	
}

void Fireball::draw(SDL_Renderer* renderer)
{
	//SDL_SetRenderDrawColor(renderer, 255, 128, 0, 255);
	SDL_Rect rect = getCamera()->transform(getBoundingBox());
	//SDL_RenderDrawRect(renderer, &rect);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	sprite.draw(renderer, rect.x, rect.y, FIREBALL_SCALE, FIREBALL_SCALE);
}

void Fireball::kill()
{
	getParentLayer()->removeObject(getId());
}
