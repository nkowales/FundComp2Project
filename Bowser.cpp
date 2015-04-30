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
#include "WinScreen.h"
#include "ScreenManager.h"
#include <cmath>
#include "HammerBro.h"
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
	setContactDamage(25);		// Damage taken by player for walking into the Bowser
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

	velocity.x = - velocity.x;
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
	state = BOW_ATK;
	inAttack = true;
	switchState = true;
	FireMagic* fire1;
	FireMagic* fire2;
	FireMagic* fire3;
	Vector2d fpos;
	// set x,y components of velocity
	Vector2d whereToShoot1 = {140,0};
	Vector2d whereToShoot2 = {137.87,24.3 };
	Vector2d whereToShoot3 = {137.87, -24.3};
	fire1 = new FireMagic(WorldObject::getUniqueID());
	fire2 = new FireMagic(WorldObject::getUniqueID());
	fire3 = new FireMagic(WorldObject::getUniqueID());
	fire1->setVelocity(whereToShoot1);
	fire2->setVelocity(whereToShoot2);
	fire3->setVelocity(whereToShoot3);
	// set spawn location
	fpos = {(facingLeft) ? position.x - 15 : position.x + BOWSER_WIDTH, position.y + (BOWSER_HEIGHT/4)};
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
void Bowser::squish(){
	
}
void Bowser::update(Uint32 time)
{
	//This function contains all the AI for Bowser
	Vector2d playerPos = getParentLayer()->getByName("PLAYER")->getPosition(); // relative position of player
	double relPlayerLocation = position.x - playerPos.x;
	double distance = abs(relPlayerLocation);
	double secs = time / 1000.;
	// decrement counters
	stunTimer -= secs;
	attackTimer -= secs;

	if (attackTimer < 0.){//Bowser is ready to attack again
		inAttack = false;
		stop();
		attackTimer = BOW_ATK_TIMER;
	}

	if (getHealth() < (BOWSER_HEALTH / 4)){ // control rage state (he powers up at low health)
		enraged = true;
		setContactDamage(100);
		sprite.changeAnimation("walk",84 ,226 , 50, 44, 0, 3);
		
	}
	if (sprite.getAnimation() != "shellSpin"){
		setInvuln(false);
	}

	if (inAir && sprite.getAnimation() != "bowJump" && velocity.y < 0){ // change animation to jump while in air
		sprite.setAnimation("jump");

	}else if (inAir && velocity.y > 0){ // When he starts to fall, go into tail smash move
		sprite.setAnimation("tailSmash");
		inAir = false;
	} 
	// Main AI Start
	if (!inAttack){ 
		if (relPlayerLocation > 0 ) // find player
		{
			playerIsLeft = true;
		}
		else if (relPlayerLocation < 0)
		{
			playerIsLeft = false;
		}
		else // if player is over, jump
		{
			jump();
		}
		if (stunTimer < 0.) // if not stunned
		{
			if (relPlayerLocation > 150 || relPlayerLocation < -150){ // chase player until in range
				if (playerIsLeft){
					walkLeft(); 
				}else{
					walkRight();	
				}
			} // when in range
			else{
				stop(); // stop running
				int spawnEnemies = rand() %200; 
				if (distance > 120){ // attack based on distance to player
					spitFlames();
				}else if (distance > 60){
					shellSpin();	
				}else if (distance > 0 && distance <=60){
					if (facingLeft){
						velocity.x = BOW_JMPSPD; 
							jump();
					} else{
						velocity.x = -BOW_JMPSPD;
						jump();
					}					
				} 
				if(spawnEnemies > 190){
					spawnEnem();
				}		
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

	if (getHealth() <= 0)
	{
		WinScreen* ws = new WinScreen(getParentLayer()->getParent());
		getParentLayer()->getParent()->getManager()->addScreen(ws);
	}

	WorldObject::update(time);
}
void Bowser::walkLeft()
{
	if(state != BOW_MVG_LEFT)
	{
		inAttack = false;
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
		inAttack =false;
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
	inAttack = false;
	state = BOW_STANDING;
	velocity.x = 0;
	sprite.setAnimation("default");
}
bool Bowser::jump()
{
	if (!inAir)
	{
		state = BOW_ATK;
		inAttack = true;
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
bool Bowser::shellSpin()
{
	state = BOW_ATK;
	inAttack = true;
	if (facingLeft)
		velocity.x = -SHELLSPIN_SPEED;
	else 
		velocity.x = SHELLSPIN_SPEED;
	sprite.setAnimation("shellSpin");
	setInvuln(true);
	return true;


}
void Bowser::stun()
{
	stunTimer = BOW_STUN_TIMER;
}
void Bowser::spawnEnem()
{
	state = BOW_ATK;
	inAttack = true;
	HammerBro* hammer1;
	HammerBro* hammer2;
	Vector2d fpos1, fpos2;
	hammer1 = new HammerBro(WorldObject::getUniqueID());
	hammer2 = new HammerBro(WorldObject::getUniqueID());
	fpos1 = {position.x + BOWSER_WIDTH + 30, position.y + (BOWSER_HEIGHT/4)};
	fpos2 = {position.x - 30, position.y + (BOWSER_HEIGHT/4)};
	hammer1->setPosition(fpos1);
	hammer2->setPosition(fpos2);
	getParentLayer()->addObject(hammer1);
	getParentLayer()->addObject(hammer2);
}

