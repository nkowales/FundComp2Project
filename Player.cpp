/*
 * Player.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: naiello
 */

#include "Player.h"
#include "ObjectLayer.h"
#include "Fireball.h"
#include "Bullet.h"

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

	//marioSprite = content->getAnimatedTexture("sprites/m-mariowithfireball.png", 45, 54, 14, 27, 0, 1, 5);
	//marioSprite.addAnimation("walk", 62, 54, 16, 27, 3, 2);

	marioSprite = content->getAnimatedTexture("sprites/mario.png", 90, 0, 16, 27, 0, 1, 5);
	marioSprite.addAnimation("walk", 90, 0, 16, 27, 1, 3);
	marioSprite.addAnimation("jump", 142, 0, 16, 28, 0, 1);
	spyroSprite = content->getAnimatedTexture("sprites/Spyro.png", 0,45,50,41,12,9,5); // 50 41
	spyroSprite.addAnimation("walk", 6, 296, 50, 44, 12, 9); // was 50 44
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
	/*SDL_Rect bbox = getCamera()->transform(getBoundingBox());
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &bbox);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);*/
	Vector2d pos = getCamera()->transform(position);
	switch (currentCharacter){
		case CH_MARIO:
			marioSprite.draw(renderer, pos.x, pos.y);
			break;
		case CH_SPYRO:
			spyroSprite.draw(renderer, pos.x, pos.y);
			break;
	}
	

	
}

void Player::handleEvent(const SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			moveRight();
			break;
		case SDLK_a:
			moveLeft();
			break;
		case SDLK_w:
			jump();
			break;
		case SDLK_s:
			duck();
			break;
		case SDLK_f:
			//rangedAttack();
			break;
		case SDLK_r:
			switchCharacter();
			break;
		}
	}
	else if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			stopMoveRight();
			break;
		case SDLK_a:
			stopMoveLeft();
			break;
		case SDLK_w:
			canJump = true;
			break;
		case SDLK_f:
			rangedAttack();
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
					moveLeft();
				}
				//Right of dead zone
				else if( e.jaxis.value > 8000 )
				{
					moveRight();
				}
				else
				{
					stopMoveRight();
					stopMoveLeft();
				}
			}
				//Y axis motion
			else if( e.jaxis.axis == 1 )
			{
				// down press
				if( e.jaxis.value > 8000 )
				{
					duck();
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
	else if (e.type == SDL_JOYBUTTONDOWN)
	{
		cout << (int)e.jbutton.button << endl;
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
			resetAnimation();
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
			resetAnimation();
		}
		break;
	}
}

void Player::jump()
{
	if (!inAir && canJump)
	{
		switch(currentCharacter){
		case CH_MARIO:
			marioSprite.setAnimation("jump");
			break;
		case CH_SPYRO:
			break;
		}
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
	Fireball* fball = new Fireball(WorldObject::getUniqueID());
	Vector2d fpos = {(facingLeft) ? position.x : position.x + PLAYER_WIDTH, position.y + PLAYER_HEIGHT / 3};
	fball->setPosition(fpos);
	if (facingLeft)
		fball->reverseDirection();
	getParentLayer()->addObject(fball);
	
	/*Bullet* bullet = new Bullet(WorldObject::getUniqueID());
	bullet->setPosition(position);
	bullet->setAngle(0.125);
	getParentLayer()->addObject(bullet);*/
}

void Player::moveLeft()
{
	if (state != PLYR_MVG_LEFT)
	{
		state = PLYR_MVG_LEFT;
		facingLeft = true;
		if (!inAir)
			switch(currentCharacter){
				case CH_MARIO:
					marioSprite.setAnimation("walk");
					marioSprite.setFlipH(true);
					break;
				case CH_SPYRO:
					spyroSprite.setAnimation("walk");
					spyroSprite.setFlipH(true);
					break;
			}			
		
	}
}

void Player::moveRight()
{
	if (state != PLYR_MVG_RIGHT)
	{
		switch(currentCharacter){
			case CH_MARIO:
				marioSprite.setAnimation("walk");
				marioSprite.setFlipH(false);
				break;
			case CH_SPYRO:
				spyroSprite.setAnimation("walk");
				spyroSprite.setFlipH(false);
				break;
		}		
		
		facingLeft = false;
		state = PLYR_MVG_RIGHT;
		
		
	}
}

void Player::stopMoveRight()
{
	if (state == PLYR_MVG_RIGHT)
	{
		switch(currentCharacter){
			case CH_MARIO:
				marioSprite.setAnimation("default");
				break;
			case CH_SPYRO:
				spyroSprite.setAnimation("default");
				break;
		}

		state = PLYR_STANDING;
	}
}

void Player::stopMoveLeft()
{
	if (state == PLYR_MVG_LEFT)
	{
		switch(currentCharacter){
			case CH_MARIO:
				marioSprite.setAnimation("default");
				break;
			case CH_SPYRO:
				spyroSprite.setAnimation("default");
				break;
		}

		state = PLYR_STANDING;
	}
}

void Player::duck()
{
	if (standingOnOneWay)
	{
		inAir = true;
		ignorePlatform = lastOneWay;
	}
}

void Player::resetAnimation()
{
	if (state == PLYR_STANDING)
	{
		switch(currentCharacter){
			case CH_MARIO:
				marioSprite.setAnimation("default");
				break;
			case CH_SPYRO:
				spyroSprite.setAnimation("default");
				break;
		}
	}
	else
	{
		switch(currentCharacter){
			case CH_MARIO:
				marioSprite.setAnimation("walk");
				break;
			case CH_SPYRO:
				spyroSprite.setAnimation("walk");
				break;
		}
	
	}
}
void Player::switchCharacter()
{
	if (currentCharacter == CH_MARIO){
		currentCharacter = CH_SPYRO;
	} else if (currentCharacter == CH_SPYRO){
		currentCharacter = CH_MARIO;
	}


}
