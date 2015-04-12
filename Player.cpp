/*
 * Player.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: naiello
 */

#include "Player.h"
#include "ObjectLayer.h"
#include "Fireball.h"

Player::Player() : WorldObject()
{
	SDL_Rect bbox;
	bbox.x = bbox.y = 0;
	bbox.w = PLAYER_WIDTH;
	bbox.h = PLAYER_HEIGHT;
	setBoundingBox(bbox);
	setCollisionGroup(COLGRP_PLAYER);
	setName("PLAYER");
}

void Player::init(ContentManager* content)
{
	// Get the camera to follow the player
	getCamera()->follow(this);

	Fireball* fball = new Fireball(100);
	fball->setPosition(position);
	getParentLayer()->addObject(fball);
}

void Player::update(Uint32 time)
{
	double secs = time / 1000.;

	// Update horizontal movement
	switch (state)
	{
	case PLYR_STANDING:
		velocity.x = 0;
		break;
	case PLYR_MVG_RIGHT:
		velocity.x = PLAYER_WALK_SPEED;
		break;
	case PLYR_MVG_LEFT:
		velocity.x = -PLAYER_WALK_SPEED;
	}

	// Apply gravity, etc.
	if (inAir)
	{
		velocity.y += GRAVITY * secs;
		standingOnOneWay = false;
	}
	else
	{
		velocity.y = 0;
	}

	// Update position, etc.
	WorldObject::update(time);

	// Make sure we haven't walked off a platform and are floating Wile E. Coyote style
	if (framesSinceTouchedGround > PLAYER_FLYING_FRAMETOL)
	{
		inAir = true;
	}
	framesSinceTouchedGround++;
}

void Player::draw(SDL_Renderer* renderer)
{
	// Right now just draw the bounding box
	SDL_Rect bbox = getCamera()->transform(getBoundingBox());
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &bbox);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Player::handleEvent(const SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			state = PLYR_MVG_RIGHT;
			break;
		case SDLK_a:
			state = PLYR_MVG_LEFT;
			break;
		case SDLK_w:
			jump();
			break;
		case SDLK_s:
			if (standingOnOneWay)
			{
				inAir = true;
				ignorePlatform = lastOneWay;
			}
			break;
		}
	}
	else if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			if (state == PLYR_MVG_RIGHT)
				state = PLYR_STANDING;
			break;
		case SDLK_a:
			if (state == PLYR_MVG_LEFT)
				state = PLYR_STANDING;
			break;
		case SDLK_w:
			canJump = true;
			break;
		}
	}
	else if (e.type == SDL_JOYAXISMOTION ){
		if (e.jaxis.which == 0 )
		{
			//X axis motion
			if( e.jaxis.axis == 0 )
			{
			//Left of dead zone
				if( e.jaxis.value < -8000 )
				{
					state = PLYR_MVG_LEFT;
				}
				//Right of dead zone
				else if( e.jaxis.value > 8000 )
				{
					state = PLYR_MVG_RIGHT;
				}
				else
				{
					state = PLYR_STANDING;
				}
			}
				//Y axis motion
			else if( e.jaxis.axis == 1 )
			{
				// down press
				if( e.jaxis.value > 8000 )
				{
					if (standingOnOneWay){
						inAir = true;
						ignorePlatform = lastOneWay;
					}
				}
				//up press
				else if( e.jaxis.value < -8000 )
				{
					jump();
					canJump = true;
				}
				else
				{
				
				}
			}

		}
	}
}

bool Player::canCollideWith(const WorldObject* other)
{
	Uint32 grp = other->getCollisionGroup();
	return ((grp == COLGRP_WORLD) || (grp == COLGRP_ONEWAY) ||
			(grp == COLGRP_PROJECTILE));
}

void Player::handleCollision(WorldObject* other, const SDL_Rect& overlap)
{
	Uint32 grp = other->getCollisionGroup();
	int feetPos = position.y + PLAYER_HEIGHT - PLAYER_FEET;

	switch (grp)
	{
	case COLGRP_WORLD: // Ordinary platform
		framesSinceTouchedGround = 0;
		ignorePlatform = NULL;
		if ((feetPos < overlap.y) && (velocity.y > 0)) // Landed on it
		{
			standingOnOneWay = false;
			inAir = false;
			position.y = other->getPosition().y - PLAYER_HEIGHT;
		}
		else if (overlap.h > overlap.w) // hit from side
		{
			if (overlap.x > position.x) // hit walking right
			{
				position.x = other->getPosition().x - PLAYER_WIDTH;
			}
			else //hit walking left
			{
				position.x = other->getPosition().x + other->getBoundingBox().w;
			}
		}
		else if ((velocity.y < 0) && (other->getPosition().y < position.y))// hit our heads
		{
			velocity.y = velocity.y * -PLAYER_HEAD_ELASTICITY;
		}
		break;
	case COLGRP_ONEWAY:
		framesSinceTouchedGround = 0;

		if ((other != ignorePlatform) && (feetPos < overlap.y) && (velocity.y > 0)) // Landed on it
		{
			lastOneWay = static_cast<OneWayPlatform*>(other);
			ignorePlatform = NULL;
			standingOnOneWay = true;
			inAir = false;
			position.y = other->getPosition().y - PLAYER_HEIGHT;
		}
		break;
	}
}

void Player::jump()
{
	if (!inAir && canJump)
	{
		inAir = true;
		canJump = false;
		position.y -= PLAYER_JUMP_TOL;
		velocity.y = -PLAYER_JUMP_VEL;
	}
}

void Player::meleeAttack()
{
	// TODO
}

void Player::rangedAttack()
{
	// TODO
}
