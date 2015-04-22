/*
 * Firewizard.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: naiello
 */

#include "FireWizard.h"
#include "ObjectLayer.h"
#include "FireMagic.h"
FireWizard::FireWizard(Uint32 id) : Enemy(id)
{

}

void FireWizard::init(ContentManager* content)
{
 	srand (time(NULL));
	setName("FireWizard");
	setBoundingBox({0, 0, FIREWIZARD_WIDTH, FIREWIZARD_HEIGHT});
	setMaxHealth(FIREWIZARD_HEALTH);
	setHealth(FIREWIZARD_HEALTH);
	setContactDamage(15);		// Damage taken by player for walking into the FIREWIZARD

	sprite = content->getAnimatedTexture("sprites/L-firewizard.png", 1, 4, 40, 38, 0, 3, 10);
	sprite.addAnimation("ranged", 1, 81, 40, 44, 0, 9);
	velocity.x = 0;
}

void FireWizard::onWalkIntoWall(WorldObject* wall, const SDL_Rect& overlap)
{
	
}

void FireWizard::draw(SDL_Renderer* renderer)
{
	SDL_Rect bbox = getCamera()->transform(getBoundingBox());
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &bbox);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	Vector2d tpos = getCamera()->transform(position);
	sprite.draw(renderer, tpos.x - 13, tpos.y);
	
}
void FireWizard::doMagic(){

	FireMagic* mag;
	Vector2d fpos;
	if (magicCooldown > 0.){}
	else
	{
		sprite.setAnimation("ranged");
		magicCooldown = MAGIC_COOLDOWN;
		mag = new FireMagic(WorldObject::getUniqueID());
		fpos = {(facingLeft) ? position.x : position.x + FIREWIZARD_WIDTH, position.y - FIREWIZARD_HEIGHT};
		mag->setPosition(fpos);
		if (facingLeft)
			mag->reverseDirection();
		getParentLayer()->addObject(mag);
	}


}
void FireWizard::squish(){
	
}
void FireWizard::update(Uint32 time)
{
	double secs = time / 1000.;
	magicCooldown -= secs;
	animTimer -= secs;
	if (animTimer >= 1.5)
	{
		switch (state)
		{
		case FW_STANDING:
			velocity.x = 0;
			break;
		case FW_MVG_RIGHT:
			velocity.x = FIREWIZARD_WALKSPD;
			break;
		case FW_MVG_LEFT:
			velocity.x = -FIREWIZARD_WALKSPD;
		}
	}
	else if (animTimer < 1.5 && animTimer >= 0 )
	{
		switch (state)
		{
		case FW_STANDING:
			break;
		case FW_MVG_RIGHT:
			stop();
			break;
		case FW_MVG_LEFT:
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
	doMagic();
	if (framesSinceTouchedGround++ > 2)
		inAir = true;

	if (inAir)
		velocity.y += GRAVITY * secs;
	else
		velocity.y = 0.;

	WorldObject::update(time);

}
void FireWizard::walkLeft()
{
	if(state != FW_MVG_LEFT)
	{
		state = FW_MVG_LEFT;
		facingLeft = true;
		sprite.setFlipH(true);

	}
}
void FireWizard::walkRight()
{
	if(state != FW_MVG_RIGHT)
	{
		state = FW_MVG_RIGHT;
		facingLeft = false;
		sprite.setFlipH(false);

	}
}
void FireWizard::stop()
{
	velocity.x = 0;
}
