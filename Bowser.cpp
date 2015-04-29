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
	sprite = content->getAnimatedTexture("sprites/M-bowser2.png", 0, 5, 50, 44, 0, 1, 13);
	sprite.addAnimation("shellSpin", 340,230,50,44,0,4);
	
	sprite.addAnimation("jump", 300,117,50,44,0,1);
	sprite.addAnimation("bowJump",100,117,50,44,0,4);
	sprite.addAnimation("walk",0,5,50,44,0,4);
	sprite.addAnimation("tailSmash", 140, 172,50,44,0,1);
	velocity.x = 0;
	Enemy::init(content);
}

void Bowser::onWalkIntoWall(WorldObject* wall, const SDL_Rect& overlap)
{
	cout << "hit wall\n";
	velocity.x = - velocity.x;
	if (facingLeft)
		position.x += 40;
	else
		position.x -= 40;


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
	// Bowser spits three fireballs when this function is called
	// after it is called, it must cool down for five seconds
	
	FireMagic* fire1;
	FireMagic* fire2;
	FireMagic* fire3;
	Vector2d fpos;

	if (fireMagicCoolDown > 0.){ return false;}
	else
	{
		// set x,y components of velocity
		Vector2d whereToShoot1 = {100,0};
		Vector2d whereToShoot2 = {90.63,42.26 };
		Vector2d whereToShoot3 = {90.63, -42.26};
		fireMagicCoolDown = FIREMAGIC_COOLDOWN;
		fire1 = new FireMagic(WorldObject::getUniqueID());
		fire2 = new FireMagic(WorldObject::getUniqueID());
		fire3 = new FireMagic(WorldObject::getUniqueID());
		fire1->setVelocity(whereToShoot1);
		fire2->setVelocity(whereToShoot2);
		fire3->setVelocity(whereToShoot3);
		// set spawn location
		fpos = {(facingLeft) ? position.x - 10 : position.x + BOWSER_WIDTH, position.y + (BOWSER_HEIGHT/4)};
		fire1->setPosition(fpos);
		fire2->setPosition(fpos);
		fire3->setPosition(fpos);
		// flip direction if facing left
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
	
}
void Bowser::update(Uint32 time)
{
	//This function contains all the AI for Bowser
	
	Vector2d playerPos = getParentLayer()->getByName("PLAYER")->getPosition(); // relative position of player
	double relPlayerlocation = position.x - playerPos.x;
	double secs = time / 1000.;
	// decrement counters
	fireMagicCoolDown -= secs;
	jumpCoolDown -= secs;
	shellSpinCoolDown -= secs;
	animTimer -= secs;
	stunTimer -= secs;
	attackTimer -= secs;
	if (getHealth() < (BOWSER_HEALTH / 4)){ // control rage state (he powers up at low health)
		enraged = true;
		setContactDamage(100);
		sprite.changeAnimation("walk",84 ,226 , 50, 44, 0, 3);
		
	}
	if (sprite.getAnimation() != "shellSpin")
		setInvuln(false);
	if (inAir && sprite.getAnimation() != "bowJump" && velocity.y < 0) // change animation to jump while in air
		sprite.setAnimation("jump");
	else if (inAir && velocity.y > 0){ // When he starts to fall, go into tail smash move
		sprite.setAnimation("tailSmash");
	} else if (!inAir){
		//if (sprite.getAnimation() == "shellSpin") // if he is tail spinning, set velocity high
			///if (facingLeft)
			//	velocity.x = 200;
			//else
				//velocity.x = -200;
		if (relPlayerlocation > 0 )
		{
			playerIsLeft = true;
		}
		else if (relPlayerlocation < 0)
		{
			playerIsLeft = false;
		}
		else // if player is over, jump
		{
			jump();
		}
		if (stunTimer < 0.) // if not stunned
		{
			
		
			
			int walk = rand() % 100; // get random value
			animTimer = ANIMATION_TIMER;
			// either walk towards player, or stop and face player
			if (animTimer < 0.){
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
			if (attackTimer < 0.){
				attackTimer = BOW_ATK_TIMER;
				if (fireMagicCoolDown < 0){ // attack with first available
					spitFlames();
				}else if (shellSpinCoolDown < 0){
					shellSpin();
				}else if (jumpCoolDown < 0){
					if (facingLeft){
						velocity.x = BOW_JMPSPD; 
						jump();
					} else{
						velocity.x = -BOW_JMPSPD;
						jump();
					}
				}else {}
			}
		}
	}
			
	if (framesSinceTouchedGround++ > 2)
		inAir = true;
		
	if (inAir) // set y velocity
		if (sprite.getAnimation() != "tailSmash"){
			velocity.y += GRAVITY * secs;
		}else {
			velocity.x = 0;
			velocity.y = 180;
		}
	else
		velocity.y = 0.;
	WorldObject::update(time);
}
void Bowser::walkLeft()
{
	if(state != BOW_MVG_LEFT)
	{
		if (!enraged)
			velocity.x = -BOWSER_WALKSPD;
		else
			velocity.x = -ENRAGED_BOW_WALKSPD;		
		state = BOW_MVG_LEFT;
		sprite.setAnimation("walk");
		facingLeft = true;
		sprite.setFlipH(true);

	}
}
void Bowser::walkRight()
{
	if(state != BOW_MVG_RIGHT)
	{
		if (!enraged)
			velocity.x = BOWSER_WALKSPD;
		else
			velocity.x = ENRAGED_BOW_WALKSPD;
		sprite.setAnimation("walk");
		state = BOW_MVG_RIGHT;
		facingLeft = false;
		sprite.setFlipH(false);

	}
}
void Bowser::stop()
{
	state = BOW_STANDING;
	velocity.x = 0;
	sprite.setAnimation("default");
}
bool Bowser::jump()
{
	
	if (jumpCoolDown > 0.){return false;}
	else {
		if (!inAir)
		{
			jumpCoolDown = JUMP_COOLDOWN;
			inAir = true;
			position.y -= 10;
			sprite.setAnimation("bowJump"); // set jump prep animation
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
		
		shellSpinCoolDown = SHELLSPIN_COOLDOWN;
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


