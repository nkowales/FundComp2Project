/*
 * Switch.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: naiello
 */

#include "Switch.h"

Switch::Switch(Uint32 id)
	: WorldObject(id)
{

}

void Switch::init(ContentManager* content)
{
	setCollisionGroup(COLGRP_WORLD);
	setBoundingBox({0, 0, 16, 16});
	position.y -= 16;
	tex = content->getAnimatedTexture("sprites/M-tile00.png", 0, 0, 16, 16, 1, 4, 10);
	tex.addAnimation("activated", 102, 68, 16, 16, 0, 1);
}

bool Switch::canCollideWith(const WorldObject* other)
{
	int colgrp = other->getCollisionGroup();
	return ((colgrp == COLGRP_PLAYER) || (colgrp == COLGRP_PROJECTILE));
}

void Switch::handleCollision(WorldObject* other, const SDL_Rect& overlap)
{
	int colgrp = other->getCollisionGroup();
	switch (colgrp)
	{
	case COLGRP_PROJECTILE:
		if (other->getName() == "[BOOMERANG]")
			activate();
		break;
	case COLGRP_PLAYER:
		if ((other->getVelocity().y < 0) && (other->getPosition().y > position.y))
			activate();
		break;
	}
}

void Switch::linkOutput(string outp, WorldOutput ptr)
{
	if (outp == "onActivate")
		onActivate = ptr;
	else
		WorldObject::linkOutput(outp, ptr);
}

void Switch::activate()
{
	if (activated)
		return;

	activated = true;

	if (onActivate)
		onActivate();

	tex.setAnimation("activated");
}

void Switch::draw(SDL_Renderer* renderer)
{
	Vector2d tpos = getCamera()->transform(position);
	tex.draw(renderer, tpos.x, tpos.y);
}
