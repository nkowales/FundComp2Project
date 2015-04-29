/*
 * Bowser.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: naiello
 *
*/
#include "Bowser.h"
#include "ObjectLayer.h"
#include "FireMagic.h"
#include "Hammer.h"
#include <cmath>
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
}

void Bowser::draw(SDL_Renderer* renderer)
{
	/*SDL_Rect bbox = getCamera()->transform(getBoundingBox());
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &bbox);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	*/
	Vector2d tpos = getCamera()->transform(position);
	sprite.draw(renderer, tpos.x - 12, tpos.y);
	Enemy::draw(renderer);
}
bool Bowser::spitFlames(){
	// TODO
	
	FireMagic* fire1;
	FireMagic* fire2;
	FireMagic* fire3;
	Vector2d fpos;

	if (fireMagicCoolDown > 0.){ return false;}
	else
	{
		//double relPlayerlocationx = position.x - playerPos.x;
		//double relPlayerlocationy = -1 *(position.y - playerPos.y);
		//double theta = atan2(relPlayerlocationx, relPlayerlocationy)
		Vector2d whereToShoot1 = {FIREMAGIC_SPEED,0};
		Vector2d whereToShoot2 = {FIREMAGIC_SPEED * sin(M_PI/3), FIREMAGIC_SPEED * cos (M_PI/3)};
		Vector2d whereToShoot3 = {FIREMAGIC_SPEED * sin(-M_PI/3), FIREMAGIC_SPEED * cos (-M_PI/3)};
		fireMagicCoolDown = FIREMAGIC_COOLDOWN;
		fire1 = new FireMagic(WorldObject::getUniqueID());
		fire2 = new FireMagic(WorldObject::getUniqueID());
		fire3 = new FireMagic(WorldObject::getUniqueID());
		fire1->setVelocity(whereToShoot1);
		fire2->setVelocity(whereToShoot2);
		fire3->setVelocity(whereToShoot3);
		fpos = {(facingLeft) ? position.x : position.x + BOWSER_WIDTH, position.y - BOWSER_HEIGHT};
		fire1->setPosition(fpos);
		fire2->setPosition(fpos);
		fire3->setPosition(fpos);
	
		if (facingLeft)
		{
			fire1->reverseDirection();
			fire2->reverseDirection();
			fire3->reverseDirection();
		}
		getParentLayer()->addObject(fire1);
		getParentLayer()->addObject(fire2);
		getParentLayer()->addObject(fire3);
		return true;
	}
	

}
void Bowser::squish(){
	hurt(5);
}
void Bowser::update(Uint32 time)
{
	//TODO
	if (getHealth() < (BOWSER_HEALTH / 4)){
		enraged = true;
		setContactDamage(100);
		
	}
	Vector2d playerPos = getParentLayer()->getByName("PLAYER")->getPosition();
	double relPlayerlocation = position.x - playerPos.x;
	double secs = time / 1000.;
	fireMagicCoolDown -= secs;
	jumpCoolDown -= secs;
	shellSpinCoolDown -= secs;
	animTimer -= secs;
	stunTimer -= secs;
	if (relPlayerlocation > 0 )
	{
		playerIsLeft = true;
	}
	else if (relPlayerlocation < 0) // don't care about if = 0 (player is directly above)
	{
		playerIsLeft = false;
	}
	else // if player is trying to jump on, do a shell spin
	{
		shellSpinCoolDown = 0;
		shellSpin();
	}
	if (stunTimer < 0.)
	{
		if (animTimer >= 1.5)
		{
			switch (state)
			{
			case BOW_STANDING:
				velocity.x = 0;
				break;
			case BOW_MVG_RIGHT:
				if (!enraged)
					velocity.x = BOWSER_WALKSPD;
				else
					velocity.x = ENRAGED_BOW_WALKSPD;
				break;
			case BOW_MVG_LEFT:
				if (!enraged)
					velocity.x = -BOWSER_WALKSPD;
				else
					velocity.x = -ENRAGED_BOW_WALKSPD;
			}
		}
		else if (animTimer < 1.5 && animTimer >= 0 )
		{
			switch (state)
			{
			case BOW_STANDING:
				break;
			case BOW_MVG_RIGHT:
				stop();
				break;
			case BOW_MVG_LEFT:
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
		if (spitFlames()){}
		else if (shellSpin()){}
		else if (jump()){}
		else {}
		if (framesSinceTouchedGround++ > 2)
			inAir = true;
	
		if (inAir)
			velocity.y += GRAVITY * secs;
		else
			velocity.y = 0.;
	}
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
bool Bowser::jump()
{
	if (jumpCoolDown > 0.){return false;}
	else {
		if (!inAir)
		{
			inAir = true;
			position.y -= 5;
			sprite.setAnimation("bowJump");
			if (facingLeft)
				velocity.x = -BOW_JMPSPD;
			else
				velocity.x = BOW_JMPSPD;		
			velocity.y = -300;
		}
		return true;
	}	
} 
bool Bowser::shellSpin()
{
	if (shellSpinCoolDown > 0.){return false;}
	else
	{
		if (facingLeft)
			velocity.x = -SHELLSPIN_SPEED;
		else 
			velocity.x = SHELLSPIN_SPEED;
		sprite.setAnimation("shellSpin");
		setInvuln(true);

	}


}
void Bowser::stun()
{
	stunTimer = BOW_STUN_TIMER;
}


