/*
 * HealthMushroom.cpp
 *
 *  Created on: Apr 29, 2015
 *      Author: naiello
 */

#include "HealthMushroom.h"

HealthMushroom::HealthMushroom(Uint32 id) : WorldObject(id)
{

}

void HealthMushroom::init(ContentManager* content)
{
	setBoundingBox({0, 0, 16, 16});
	setCollisionGroup(COLGRP_POWERUP);
	tex = content->getAnimatedTexture("sprites/M-misc.png", 161, 69, 16, 16, 0, 1, 100);
}

void HealthMushroom::draw(SDL_Renderer* renderer)
{
	Vector2d tpos = getCamera()->transform(position);
	tex.draw(renderer, tpos.x, tpos.y);
}
