/*
 * Bowser.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: naiello
 */

#include "Bowser.h"
#include "ObjectLayer.h"
#include "Hammer.h"
Bowser::Bowser(Uint32 id) : Enemy(id)
{

}

void Bowser::init(ContentManager* content)
{
 	srand (time(NULL));
	setName("Bowser");
	setBoundingBox({0, 0, BOWSER_WIDTH, BOWSER_HEIGHT});
	setMaxHealth(BOWSER_HEALTH);
	setHealth(BOWSER_HEALTH);
	setContactDamage(50);		// Damage taken by player for walking into the Bowser

	sprite = content->getAnimatedTexture("sprites/M-Bowser2.png", 0, 5, 50, 44, 0, 1, 7);
	sprite.addAnimation("shellSpin", 340,230,50,44,0,4);
	sprite.addAnimation("enraged",84 ,226 , 50, 44, 0, 3);
	sprite.addAnimation("bowserJump",50,62,50,44,0,4);
	sprite.addAnimation("walk",0,5,50,44,0,4);
	velocity.x = 0;
}

void Bowser::onWalkIntoWall(WorldObject* wall, const SDL_Rect& overlap)
{
	jump();
}

void Bowser::draw(SDL_Renderer* renderer)
{
	/*SDL_Rect bbox = getCamera()->transform(getBoundingBox());
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &bbox);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);*/
	Vector2d tpos = getCamera()->transform(position);
	sprite.draw(renderer, tpos.x - 12, tpos.y);
	Enemy::draw(renderer);
}
void Bowser::spitFlames(){
	// TODO
	/*
	Hammer* ham;
	Vector2d fpos;
	if (hammerCooldown > 0.){}
	else
	{
		sprite.setAnimation("ranged");
		hammerCooldown = HAMMER_COOLDOWN;
		ham = new Hammer(WorldObject::getUniqueID());
		fpos = {(facingLeft) ? position.x : position.x + BOWSER_WIDTH, position.y - BOWSER_HEIGHT};
		ham->setPosition(fpos);
		if (facingLeft)
			ham->reverseDirection();
		getParentLayer()->addObject(ham);
	}
	*/

}
void Bowser::squish(){
	
}
void Bowser::update(Uint32 time)
{
	//TODO
	/*
	double secs = time / 1000.;
	
	animTimer -= secs;
	if (animTimer >= 1.5)
	{
		switch (state)
		{
		case STANDING:
			velocity.x = 0;
			break;
		case MVG_RIGHT:
			velocity.x = BOWSER_WALKSPD;
			break;
		case MVG_LEFT:
			velocity.x = -BOWSER_WALKSPD;
		}
	}
	else if (animTimer < 1.5 && animTimer >= 0 )
	{
		switch (state)
		{
		case STANDING:
			break;
		case MVG_RIGHT:
			stop();
			break;
		case MVG_LEFT:
			stop();
			break;
		}

	}
	else{
		int randWalk = rand() % 100;
		
		if ( randWalk > 49 )
		{
			animTimer = ANIMATION_TIMER;
			walkLeft();
		} 
		else if (randWalk <= 49)
		{
			animTimer = ANIMATION_TIMER;
			walkRight();	
		}
	}
	throwHammer();
	if (framesSinceTouchedGround++ > 2)
		inAir = true;

	if (inAir)
		velocity.y += GRAVITY * secs;
	else
		velocity.y = 0.;
	*/
	WorldObject::update(time);

}
void Bowser::walkLeft()
{
	if(state != BOW_MVG_LEFT)
	{
		state = BOW_MVG_LEFT;
		facingLeft = true;
		sprite.setFlipH(true);

	}
}
void Bowser::walkRight()
{
	if(state != BOW_MVG_RIGHT)
	{
		state = BOW_MVG_RIGHT;
		facingLeft = false;
		sprite.setFlipH(false);

	}
}
void Bowser::stop()
{
	velocity.x = 0;
}
void Bowser::jump()
{
	if (!inAir && canJump)
	{
		inAir = true;
		canJump = false;
		position.y -= 5;		
		velocity.y = -300;
	}
		
} 
