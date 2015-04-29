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

	sprite = content->getAnimatedTexture("sprites/M-goomba.png", 15, 4, 16, 16, 34, 2, 20);
	sprite.addAnimation("squish", 314, 4, 17,16, 0, 1);
	velocity.x = -GOOMBA_WALKSPEED;
}

void Goomba::onWalkIntoWall(WorldObject* wall, const SDL_Rect& overlap)
{
	velocity.x = -velocity.x;
	walkingLeft = !walkingLeft;

	position.x += (walkingLeft) ? -2 : 2;
}

void Goomba::draw(SDL_Renderer* renderer)
{
	/*SDL_Rect bbox = getCamera()->transform(getBoundingBox());
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &bbox);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);*/
	Vector2d tpos = getCamera()->transform(position);
	sprite.draw(renderer, tpos.x, tpos.y);

	Enemy::draw(renderer);
}
void Goomba::update(Uint32 time)
{
	if (getStunTimer() > 0.)
	{
		velocity.x = 0.;
	}
	else
	{
		velocity.x = (walkingLeft) ? -GOOMBA_WALKSPEED : GOOMBA_WALKSPEED;
	}

	Enemy::update(time);
}
void Goomba::squish(){
	sprite.setAnimation("squish");
	
	die();
}

void Goomba::stun()
{
	setStunTimer(GOOMBA_STUNTIME);
}
