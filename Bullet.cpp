/*
 * Bullet.cpp
 *
 *  Created on: Apr 12, 2015
 *      Author: naiello
 */

#include "Bullet.h"
#include "ObjectLayer.h"
#include <cmath>

Bullet::Bullet(Uint32 id) : WorldObject(id)
{
	setCollisionGroup(COLGRP_PROJECTILE);
}

void Bullet::init(ContentManager* content)
{
	endpoint.x = BULLET_SIZE * cos(angle);
	endpoint.y = BULLET_SIZE * sin(angle);
	SDL_Rect bbox = {0, 0, BULLET_SIZE, BULLET_SIZE};
	setBoundingBox(bbox);
}

bool Bullet::canCollideWith(const WorldObject* other)
{
	int colgrp = other->getCollisionGroup();
	return (colgrp == COLGRP_WORLD);
}

void Bullet::handleCollision(WorldObject* other, const SDL_Rect& overlap)
{
	getParentLayer()->removeObject(getId());
}

void Bullet::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	Vector2d p1 = getCamera()->transform(position);
	Vector2d p2 = {position.x + endpoint.x, position.y + endpoint.y};
	p2 = getCamera()->transform(p2);
	SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
	/*SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	SDL_Rect bbox = getCamera()->transform(getBoundingBox());
	SDL_RenderDrawRect(renderer, &bbox);*/
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Bullet::setAngle(double ang)
{
	angle = ang;
	//angle = atan(velocity.y / velocity.x);
	endpoint.x = BULLET_SIZE * cos(angle);
	endpoint.y = BULLET_SIZE * sin(angle);
	velocity.x = BULLET_SPEED * cos(angle);
	velocity.y = BULLET_SPEED * sin(angle);
}
