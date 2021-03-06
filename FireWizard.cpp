/*
 * Firewizard.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: naiello
 */

#include "FireWizard.h"
#include "ObjectLayer.h"
#include "FireMagic.h"
#include <cmath>
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
	if (state == FW_MVG_RIGHT)
		walkLeft();
	else if (state == FW_MVG_LEFT)
		walkRight();
}

void FireWizard::draw(SDL_Renderer* renderer)
{
	
	/*SDL_Rect bbox = getCamera()->transform(getBoundingBox());
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &bbox);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	*/
	Vector2d tpos = getCamera()->transform(position);
	if (sprite.getAnimation() == "ranged"){
		sprite.draw(renderer, tpos.x - 13, tpos.y - 6);
	} else {
		sprite.draw(renderer, tpos.x - 13, tpos.y);
	}
	Enemy::draw(renderer);
}
void FireWizard::doMagic(){
	if (magicCooldown > 0.)
		return;

	Vector2d playerPos = getParentLayer()->getByName("PLAYER")->getPosition();
	double rx = playerPos.x - position.x;
	double ry = playerPos.y - position.y;
	//double theta = atan2(relPlayerlocationx, relPlayerlocationy);
	double dist = sqrt(rx * rx + ry * ry);
	double xvel = FIREMAGIC_SPEED * (rx / dist);
	double yvel = FIREMAGIC_SPEED * (ry / dist);
	Vector2d whereToShoot = {xvel,yvel};
	FireMagic* mag;
	Vector2d fpos;

	sprite.setAnimation("ranged");
	magicCooldown = MAGIC_COOLDOWN;
	mag = new FireMagic(WorldObject::getUniqueID());
	//if (facingLeft)
		//mag->setFlipH(true);
	fpos = {(facingLeft) ? position.x : position.x + FIREWIZARD_WIDTH, position.y + (FIREWIZARD_HEIGHT / 3)};
	mag->setPosition(fpos);
	mag->setVelocity(whereToShoot);
	//if (facingLeft)
		//mag->reverseDirection();
	getParentLayer()->addObject(mag);


}
void FireWizard::squish()
{
	hurt(5);
}
void FireWizard::update(Uint32 time)
{
	Vector2d playerPos = getParentLayer()->getByName("PLAYER")->getPosition();
	double relPlayerlocation = position.x - playerPos.x;
	double secs = time / 1000.;
	magicCooldown -= secs;
	animTimer -= secs;

	if (relPlayerlocation > 0 )
	{
		playerIsLeft = true;
	}
	else // don't care about if = 0 (player is directly above)
	{
		playerIsLeft = false;
	}
	if (getStunTimer() <= 0.){
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
			int walk = rand() % 100; // get random value
			animTimer = ANIMATION_TIMER;
			// either walk towards player, or stop and face player
			if ( walk > 49 )
			{
				if (playerIsLeft)
					walkLeft(); 
				else
					walkRight();
			} 
			else if (walk <= 49)
			{
				if (playerIsLeft)
				{
					stop();
					facingLeft = true;
					sprite.setFlipH(true);
				}
				else 	
				{
					stop();
					facingLeft = false;
					sprite.setFlipH(false);
				}
			}
		}
		doMagic();
	}
	else
	{
		velocity.x = 0;
	}
	/*if (framesSinceTouchedGround++ > 2)
		inAir = true;

	if (inAir)
		velocity.y += GRAVITY * secs;
	else
		velocity.y = 0.;*/

	Enemy::update(time);

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
void FireWizard::stun()
{
	setStunTimer(FIREWIZARD_STUNTIME);
}
