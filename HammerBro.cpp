/*
 * HammerBro.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: naiello
 */

#include "HammerBro.h"
#include "ObjectLayer.h"
#include "Hammer.h"
HammerBro::HammerBro(Uint32 id) : Enemy(id)
{

}

void HammerBro::init(ContentManager* content)
{
 	srand (time(NULL));
	setName("HammerBro");
	setBoundingBox({0, 0, HAMMERBRO_WIDTH, HAMMERBRO_HEIGHT});
	setMaxHealth(HAMMERBRO_HEALTH);
	setHealth(HAMMERBRO_HEALTH);
	setContactDamage(15);		// Damage taken by player for walking into the HammerBro

	sprite = content->getAnimatedTexture("sprites/M-hammerkoopa.png", 1, 10, 40, 29, 0, 4, 10);
	sprite.addAnimation("ranged", 160, 10, 40, 29, 0, 3);
	velocity.x = 0;
}

void HammerBro::onWalkIntoWall(WorldObject* wall, const SDL_Rect& overlap)
{
	
}

void HammerBro::draw(SDL_Renderer* renderer)
{
	SDL_Rect bbox = getCamera()->transform(getBoundingBox());
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &bbox);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	Vector2d tpos = getCamera()->transform(position);
	sprite.draw(renderer, tpos.x - 12, tpos.y);
	
}
void HammerBro::throwHammer(){

	Hammer* ham;
	Vector2d fpos;
	if (hammerCooldown > 0.){}
	else
	{
		sprite.setAnimation("ranged");
		hammerCooldown = HAMMER_COOLDOWN;
		ham = new Hammer(WorldObject::getUniqueID());
		fpos = {(facingLeft) ? position.x : position.x + HAMMERBRO_WIDTH, position.y - HAMMERBRO_HEIGHT};
		ham->setPosition(fpos);
		if (facingLeft)
			ham->reverseDirection();
		getParentLayer()->addObject(ham);
	}


}
void HammerBro::squish(){
	die();
}
void HammerBro::update(Uint32 time)
{
	double secs = time / 1000.;
	hammerCooldown -= secs;
	animTimer -= secs;
	if (animTimer >= 1.5)
	{
		switch (state)
		{
		case STANDING:
			velocity.x = 0;
			break;
		case MVG_RIGHT:
			velocity.x = HAMMERBRO_WALKSPD;
			break;
		case MVG_LEFT:
			velocity.x = -HAMMERBRO_WALKSPD;
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
		cout << randWalk << endl;
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

	WorldObject::update(time);

}
void HammerBro::walkLeft()
{
	if(state != MVG_LEFT)
	{
		state = MVG_LEFT;
		facingLeft = true;
		sprite.setFlipH(true);

	}
}
void HammerBro::walkRight()
{
	if(state != MVG_RIGHT)
	{
		state = MVG_RIGHT;
		facingLeft = false;
		sprite.setFlipH(false);

	}
}
void HammerBro::stop()
{
	velocity.x = 0;
}
