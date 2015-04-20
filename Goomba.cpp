/*
 * Goomba.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: naiello
 */

#include "Goomba.h"

Goomba::Goomba(Uint32 id) : Enemy(id)
{

}

void Goomba::init(ContentManager* content)
{
	setBoundingBox({0, 0, GOOMBA_SIZE, GOOMBA_SIZE});
	setMaxHealth(GOOMBA_HEALTH);
	setHealth(GOOMBA_HEALTH);
	setContactDamage(10);		// Damage taken by player for walking into the goomba

	sprite = content->getAnimatedTexture("sprites/m-enemies.png", 15, 4, 16, 16, 34, 2, 20);
	velocity.x = -GOOMBA_WALKSPEED;
}

void Goomba::onWalkIntoWall(WorldObject* wall, const SDL_Rect& overlap)
{
	velocity.x = -velocity.x;
}

void Goomba::draw(SDL_Renderer* renderer)
{
	Vector2d tpos = getCamera()->transform(position);
	sprite.draw(renderer, tpos.x, tpos.y);
}
