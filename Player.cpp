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
#include "Boomerang.h"
#include "Enemy.h"
#include "Hammer.h"
#include "ObjectLayer.h"
#include "Geom.h"
#include "ScreenManager.h"
#include "DeathScreen.h"
#include "PauseScreen.h"

Player::Player() : WorldObject(), healthBar(maxHealth)
{
	SDL_Rect bbox;
	bbox.x = bbox.y = 0;
	bbox.w = MARIO_WIDTH;
	bbox.h = MARIO_HEIGHT;
	setBoundingBox(bbox);
	setCollisionGroup(COLGRP_PLAYER);
	setName("PLAYER");
	healthBar.setBackground({75, 0, 0, 255});
	healthBar.setForeground({200, 0, 0, 255});
	healthBar.setBorder({75, 0, 0, 255});
}

void Player::init(ContentManager* content)
{
	// Get the camera to follow the player
	getCamera()->follow(this);

	Mix_Chunk* jump;
	Mix_Chunk* damage;	
	Mix_Chunk* lowHealth;
	Mix_Chunk* attack;
	Mix_Chunk* wallColl;
	AnimatedTexture marioSprite, spyroSprite, lBlueSprite, linkSprite;
	// Animations are loaded in the following format:
	// ("name", xpos, ypos, width, height,  pixels in betwen, frames, [framerate])
	marioSprite = content->getAnimatedTexture("sprites/M-Mario.png", 90, 0, 16, 27, 0, 1, 8);
	marioSprite.addAnimation("walk", 90, 0, 16, 27, 1, 3); 
	marioSprite.addAnimation("jump", 142, 0, 16, 28, 0, 1);

	spyroSprite = content->getAnimatedTexture("sprites/S-Spyro2.png", 0,28,100,60,16,1,7); // 50 41
	spyroSprite.addAnimation("walk", 0, 381, 100, 60, 0, 8); // 396, 46
	spyroSprite.addAnimation("jump", 0, 975, 100, 60, 0, 9);
	spyroSprite.addAnimation("flying", 0, 1305, 100, 60, 0, 8);
	spyroSprite.addAnimation("glide",500 ,975 , 100, 60, 0, 4);
	spyroSprite.addAnimation("melee",5 ,1898 , 100, 51, 0, 9);

	linkSprite = content->getAnimatedTexture("sprites/L-Link2.png", 1, 107, 56, 24, 0, 1, 10);
	linkSprite.addAnimation("walk", 1, 215, 56, 24, 0, 6);
	linkSprite.addAnimation("ranged", 1, 481, 56, 26, 0, 5);
	linkSprite.addAnimation("melee", 1, 19, 56, 35, 0, 9); // maybe expand to 15 frames
	linkSprite.addAnimation("jump", 1, 216, 56, 23, 0, 1); 
	linkSprite.addAnimation("defend", 1, 144, 56, 24, 0, 1);
	

	sprites.push_back(marioSprite);
	sprites.push_back(linkSprite);
	sprites.push_back(spyroSprite);

	jump = content->getSfx("Music/smb_jump-small.wav");
	damage = content->getSfx("Music/LOZ_Hit.wav");
	lowHealth = content->getSfx("Music/AOL_LowHealth.wav");
	attack = content->getSfx("Music/LOZ_Sword.wav");
	wallColl = content->getSfx("Music/smb_bump.wav");
	sfx.push_back(jump);
	sfx.push_back(damage);
	sfx.push_back(lowHealth);
	sfx.push_back(attack);
	sfx.push_back(wallColl);
}	 

void Player::update(Uint32 time)
{

	double secs = time / 1000.;
	sfxTimer -= secs;
	if (health < PLAYER_MAXHEALTH /4){
		Mix_PlayChannel(-1, sfx[SFX_LOWHLTH], 0);
	}
	// Reset the bounding box when we're standing still
	if (sprites[currentCharacter].getAnimation() == "default"){
		resetBBox();
	}

	// Update timers
	if (fireballCooldown > 0.)
		fireballCooldown -= secs;

	if (invulnTimer > 0.)
		invulnTimer -= secs;

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
		break;
	case PLYR_HOVERING:
		velocity.x = 0;
		velocity.y = 0;
		break;
	case PLYR_FLYING_RIGHT:
		velocity.x = PLAYER_WALK_SPEED;
		break;
	case PLYR_FLYING_LEFT:
		velocity.x = -PLAYER_WALK_SPEED;
		break;
	case PLYR_FLYING_UP:
		velocity.y = -PLAYER_WALK_SPEED;
		break;
	case PLYR_FLYING_DOWN:
		velocity.y = PLAYER_WALK_SPEED;
		break;
	
	}

	// Apply gravity, etc.
	if (inAir)
	{
		if (flying){
			if (sprites[CH_SPYRO].getAnimation()!= "flying")
			{
				sprites[CH_SPYRO].setAnimation("flying");
				sprites[CH_SPYRO].setRate(7);	
			}
		}

		// Handle Spyro's flying/gliding animations
		if ( velocity.y > 10 && currentCharacter == CH_SPYRO){
			if (!flying)
			{
				if (sprites[CH_SPYRO].getAnimation() != "glide"){
					sprites[CH_SPYRO].setAnimation("glide");
					sprites[CH_SPYRO].setRate(7);
					
				}
				velocity.y += SPYRO_GRAVITY*secs;
			}
			else
			{
				//if (sprites[CH_SPYRO].getAnimation()!= "flying")
				//{
				//	sprites[CH_SPYRO].setAnimation("flying");
				//	sprites[CH_SPYRO].setRate(7);	
				//}
				
			}
			
		}else{
			velocity.y += (GRAVITY) * secs;
		}	
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
	// comment / uncomment these next four lines to get bounding box to show up
	/*SDL_Rect bbox = getCamera()->transform(getBoundingBox());
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &bbox);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);*/

	healthBar.draw(renderer, {HEALTHBAR_OFFSET, HEALTHBAR_OFFSET, HEALTHBAR_W, HEALTHBAR_H}, health);

	if (invulnTimer > 0.)
	{
		int blink = (int)(invulnTimer * 10) % 2;
		if (blink)
			return;
	}

	double sx = 1.;
	double sy = 1.;

	if (currentCharacter == CH_SPYRO)
		sx = sy = 0.75;

	// Position correction
	Vector2d pos = getCamera()->transform(position);
	if (currentCharacter != CH_LINK && currentCharacter!= CH_SPYRO){
		sprites[currentCharacter].draw(renderer, pos.x, pos.y, sx, sy);
	} else if (currentCharacter == CH_SPYRO){
		sprites[currentCharacter].draw(renderer, pos.x-15, pos.y -15, sx,sy);
	}else {
		sprites[currentCharacter].draw(renderer, pos.x-17, pos.y, sx, sy);
	}
}

void Player::handleEvent(const SDL_Event& e)
{
	PauseScreen* pscreen;
	sprites[CH_LINK].setRate(8);

	// Most of these actions are stored as subroutines so they can be called from the
	// keyboard or the joystick sections equivalently.  See relevant subroutines for more info.

	if (e.type == SDL_KEYDOWN)
	{
		cout << state << endl;
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			if (flying)	
				flyRight();
			else
				moveRight();
			break;
		case SDLK_a:
			if (flying)
				flyLeft();
			else
				moveLeft();
			break;
		case SDLK_w:

			if (flying && currentCharacter == CH_SPYRO)
				flyUp();
			else
				jump();
			break;
		case SDLK_s:
			if (flying && currentCharacter == CH_SPYRO)
				flyDown();
			else
				duck();
			break;
		case SDLK_f:
			//rangedAttack();
			break;
		case SDLK_1:
			switchCharacter(CH_MARIO);
			break;
		case SDLK_2:
			switchCharacter(CH_LINK);
			break;
		case SDLK_3:
			switchCharacter(CH_SPYRO);
			break;
		case SDLK_r:
			switchMode(); // switch link from offense to defense
			break;
		case SDLK_c:
			defend();
			break;
		case SDLK_ESCAPE:
			pscreen = new PauseScreen(getParentLayer()->getParent());
			getParentLayer()->getParent()->getManager()->addScreen(pscreen);
			break;
		}
	}
	else if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			if (flying)
				stopFlyRight();
			else
				stopMoveRight();
			break;
		case SDLK_a:
			if (flying)
				stopFlyLeft();
			else
				stopMoveLeft();
			break;
		case SDLK_w:
			if (flying)
				stopFlyUp();
			else
				canJump = true;
			break;
		case SDLK_f:
			rangedAttack();
			break;
		case SDLK_e:
			meleeAttack();
			break;
		case SDLK_c:
			if (currentCharacter == CH_LINK)
				resetAnimation();
			break;
		case SDLK_s:
			if (flying)	
				stopFlyDown();
		}
		cout << state  << endl;
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
					if (flying)
						flyLeft();
					else
						moveLeft();
				}
				//Right of dead zone
				else if( e.jaxis.value > 8000 )
				{
					if (flying)
						flyRight();
					else
						moveRight();
				}
				else
				{
					switch (state)
					{
					case PLYR_MVG_LEFT:
						stopMoveLeft();
						break;
					case PLYR_MVG_RIGHT:
						stopMoveRight();
						break;
					case PLYR_FLYING_LEFT:
						stopFlyLeft();
						break;
					case PLYR_FLYING_RIGHT:
						stopFlyRight();
						break;
					case PLYR_FLYING_UP:
						stopFlyUp();
						break;
					case PLYR_FLYING_DOWN:
						stopFlyDown();
						break;
					}
				}
			}
				//Y axis motion
			else if( e.jaxis.axis == 1 )
			{
				// down press
				if( e.jaxis.value > 8000 )
				{
					if (flying && currentCharacter == CH_SPYRO)
						flyDown();
					else
						duck();
				}
				//up press
				else if( e.jaxis.value < -8000 )
				{
					if (flying && currentCharacter == CH_SPYRO)
						flyUp();
					//else
					//	jump();
					
					//canJump = true;
				}
				else{
					switch (state)
					{
					case PLYR_MVG_LEFT:
						stopMoveLeft();
						break;
					case PLYR_MVG_RIGHT:
						stopMoveRight();
						break;
					case PLYR_FLYING_LEFT:
						stopFlyLeft();
						break;
					case PLYR_FLYING_RIGHT:
						stopFlyRight();
						break;
					case PLYR_FLYING_UP:
						stopFlyUp();
						break;
					case PLYR_FLYING_DOWN:
						stopFlyDown();
						break;
					}
				}

			}

		}
	}
	else if (e.type == SDL_JOYBUTTONDOWN)
	{
		int buttonPress =(int)e.jbutton.button;
		switch (buttonPress)
		{
		case 4:
			switchCharacter(CH_MARIO);
			break;
		case 5:
			switchCharacter(CH_LINK);
			break;
		case 6:
			switchCharacter(CH_SPYRO);
			break;
		case 7:
			switchMode(); // switch link from offense to defense
			break;
		case 0:
			defend();
			break;
		case 3:
			jump();
			canJump=true;
			break;
		case 8:
			pscreen = new PauseScreen(getParentLayer()->getParent());
			getParentLayer()->getParent()->getManager()->addScreen(pscreen);
			break;
		}
	}
	else if (e.type == SDL_JOYBUTTONUP)
	{
		int buttonPress =(int)e.jbutton.button;
		switch (buttonPress)
		{
		//case SDLK_w:
		//	if (flying)
		//		state = PLYR_HOVERING;
		//	else
		//		canJump = true;
		//	break;
		case 1:
			rangedAttack();
			break;
		case 2:
			meleeAttack();
			break;
		case 0:
			if (currentCharacter == CH_LINK)
				resetAnimation();
			break;
		case SDLK_s:
			if (flying)	
				state = PLYR_HOVERING;
		}
	}
}

// What can we collide with?
bool Player::canCollideWith(const WorldObject* other)
{
	Uint32 grp = other->getCollisionGroup();
	
	return ((grp == COLGRP_WORLD) || (grp == COLGRP_ONEWAY) ||
			(grp == COLGRP_PROJECTILE) || (grp == COLGRP_ENEMY) || (grp == COLGRP_ENEMPROJECTILE) || 
			(grp == COLGRP_ADVANCE) || (grp == COLGRP_POWERUP));
	
}

void Player::handleCollision(WorldObject* other, const SDL_Rect& overlap)
{
	Uint32 grp = other->getCollisionGroup();
	int feetPos;
	SDL_Rect bbox = getBoundingBox();
	feetPos = position.y + bbox.h - PLAYER_FEET;
	Boomerang* boom;
	Enemy* enemy;
	Hammer* ham;

	switch (grp)
	{
	case COLGRP_WORLD: // Ordinary platform
		//cout << "[ " << position.x << ", " << position.y << " ]" << endl;
		if (feetPos < other->getPosition().y){
			framesSinceTouchedGround = 0;
		}
		ignorePlatform = NULL;
		if ((feetPos < other->getPosition().y) && (velocity.y > 0) && (overlap.w > 2)) // Landed on it
		{
			land();
			standingOnOneWay = false;
			inAir = false;
			position.y = other->getPosition().y - bbox.h;
			if (!flying)
				resetAnimation();
		}
		else if (overlap.h > overlap.w) // hit from side
		{
			if (state == PLYR_MVG_LEFT || state == PLYR_MVG_RIGHT)
			
				if (sfxTimer <0.){
					Mix_PlayChannel(-1, sfx[SFX_WALLCOL], 0);
					sfxTimer = 0.4;
				}
				else
					sfxTimer -= .005;
			if (overlap.x > bbox.x) // hit walking right
			{
				position.x = other->getPosition().x - bbox.w - (bbox.x - position.x);
				
			}
			else //hit walking left
			{
				position.x = other->getPosition().x + other->getBoundingBox().w - (bbox.x - position.x);
			}
		}
		else if ((velocity.y < 0) && (other->getPosition().y < position.y) && (overlap.w > 2))// hit our heads
		{
			position.y = other->getPosition().y + other->getBoundingBox().h + 1;
			velocity.y = velocity.y * -PLAYER_HEAD_ELASTICITY;
		}
		break;
	case COLGRP_ONEWAY:	// For one way platforms, we only check to see if we landed on it
		if (feetPos < other->getPosition().y)
			framesSinceTouchedGround = 0;

		if ((other != ignorePlatform) && (feetPos < other->getPosition().y) && (velocity.y > 0) && (overlap.h < 5)) // Landed on it
		{
			land();
			lastOneWay = static_cast<OneWayPlatform*>(other);
			ignorePlatform = NULL;
			standingOnOneWay = true;
			inAir = false;
			position.y = other->getPosition().y - bbox.h;
			if (currentCharacter != CH_SPYRO)	
				resetAnimation();
		}
		break;
	case COLGRP_PROJECTILE:		// Got the boomerang back
			boom = dynamic_cast<Boomerang*>(other);
			if (boom && boom->isReturning())
				hasBoomerang = true;
			break;

	case COLGRP_ENEMY:		// ouch
		enemy = static_cast<Enemy*>(other);
		if (sprites[currentCharacter].getAnimation() == "melee" && !inAir) // melee collision not in air
		{
			if ((facingLeft && (position.x > enemy->getPosition().x))
				|| (!facingLeft && (position.x < enemy->getPosition().x)))
			{
				
				enemy->hurt(SWORD_DAMAGE);
			}
		}
		else if ((feetPos < overlap.y) && (velocity.y > 0)) // landed on it
		{
			Mix_PlayChannel(-1, sfx[SFX_JMP], 0);
			enemy->squish();
			velocity.y= velocity.y * -1;
		}
		else
		{
			if (overlap.h > overlap.w) // hit from side
			{
				if (overlap.x > bbox.x) // hit walking right
				{
					if (defending){
						hurt(0);
						position.x = other->getPosition().x - bbox.w - (bbox.x - position.x);
					}
					else if (!enemy->isStunned()){
						hurt(enemy->getContactDamage());					
						
					}
				}
				else //hit walking left
				{
					if (defending){
						hurt(0);
						position.x = other->getPosition().x + other->getBoundingBox().w - (bbox.x - position.x);	 				
					}
					else{
						hurt(enemy->getContactDamage());	
						
					}				
				}
			}
		}
		break;
	case COLGRP_ENEMPROJECTILE:
		ham = static_cast<Hammer*>(other);
		if (inAir) // hit in the air
			hurt(ham->getContactDamage());
		else if ( (feetPos > overlap.y) ) // hit on head
		{
			hurt(ham->getContactDamage());

		} 
		else 
		{
			if (facingLeft)
			{
				if (ham->getXVel() < 0) // hit on back
				{
					hurt(ham->getContactDamage());
				}
				else if (defending)
				{
					hurt(0);
				}	
				else
				{
					hurt(ham->getContactDamage());
				}

			}
			else 
			{
				if (ham->getXVel() > 0) // hit on back
				{
					hurt(ham->getContactDamage());
				}
				else if (defending) // if defending
				{
					hurt(0);
				}	
				else		// if not defending
				{
					hurt(ham->getContactDamage());
				}
			}
		}
		break;

	case COLGRP_POWERUP:		// heal up
		health += 40;
		if (health > maxHealth)
			health = maxHealth;

		getParentLayer()->removeObject(other->getId());
		break;
	}
}

void Player::jump()
{
	defending = false; // takes care of any false, lingering flags
	if (!inAir && canJump) // if able to take a jump
	{
		Mix_PlayChannel(-1, sfx[SFX_JMP], 0);
		for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
		{
			iter->setAnimation("jump"); // set all animations to jump
		}

		sprites[CH_SPYRO].setRate(8); // adjust spyro's speed
		inAir = true;
		canJump = false;

		position.y -= PLAYER_JUMP_TOL;
		if (currentCharacter != CH_SPYRO)
		{
			velocity.y = -PLAYER_JUMP_VEL; // spyro has a different jumping velocity
		}
		else
		{
			
			velocity.y = -SPYRO_JUMP_VEL;
		}
	}
}

void Player::meleeAttack()
{
	defending = false;
	SDL_Rect bbox;
	velocity.x = 0;
	
	switch(currentCharacter){
		case CH_LINK:
			Mix_PlayChannel(-1, sfx[SFX_ATK], 0);
			if (facingLeft) // update bounding box / set animation to melee
			{
				sprites[CH_LINK].setAnimation("melee");
				sprites[CH_LINK].setRate(3);
				bbox.x = -15;
				bbox.y = 0;
				bbox.w = 35;
				bbox.h = LINK_HEIGHT;
				setBoundingBox(bbox);
			}
			else {	
				sprites[CH_LINK].setAnimation("melee");
				sprites[CH_LINK].setRate(1);
				sprites[currentCharacter].setFlipH(false);
				bbox.x = 0;
				bbox.y = 0;
				bbox.w = 36;
				bbox.h = LINK_HEIGHT;
				setBoundingBox(bbox);
			} 
			
		break;
		case CH_SPYRO:
			sprites[CH_SPYRO].setAnimation("melee");
			
			break;
		default:
			break;
	}
	// TODO
}

void Player::rangedAttack()
{
	defending = false;
	Fireball* fball; // declare possible ranged missiles
	Boomerang* boom;
	Vector2d fpos;
	string current;
	switch(currentCharacter)
	{
		case CH_MARIO:
			if (fireballCooldown > 0.) break; // if still in cooldown period, break

			fireballCooldown = FIREBALL_COOLDOWN; // reset cooldown

			fball = new Fireball(WorldObject::getUniqueID());

			fpos = {(facingLeft) ? position.x : position.x + MARIO_WIDTH, position.y + MARIO_HEIGHT / 3}; // set spawn point
			fball->setPosition(fpos);

			if (facingLeft)
				fball->reverseDirection();

			getParentLayer()->addObject(fball);
			break;
		case CH_LINK:
			// Make sure we haven't already thrown
			if (!hasBoomerang) break;
			hasBoomerang = false;

			// Handle the animation
			sprites[CH_LINK].setAnimation("ranged");
			current = sprites[CH_LINK].getAnimation();

			// Spawn point of the boomerang
			fpos = {(facingLeft) ? position.x : position.x + LINK_WIDTH, position.y + LINK_HEIGHT / 3};

			// Trace out the control points for the bezier path
			Path p;
			if (facingLeft)
			{
				p.push_back(fpos);
				p.push_back({fpos.x - BOOMERANG_RANGE, fpos.y + 25});
				p.push_back({fpos.x - BOOMERANG_RANGE + 25, fpos.y - 50});
				p.push_back({fpos.x - BOOMERANG_RANGE, fpos.y - 100});
			}
			else
			{
				p.push_back(fpos);
				p.push_back({fpos.x + BOOMERANG_RANGE, fpos.y + 25});
				p.push_back({fpos.x + BOOMERANG_RANGE + 25, fpos.y - 50});
				p.push_back({fpos.x + BOOMERANG_RANGE, fpos.y - 100});
			}

			boom = new Boomerang(WorldObject::getUniqueID());
			boom->setPath(p);					 // Calculates bezier path from control points
			boom->setReturnTarget(this);			// Return to the player after it completes the path
			boom->setPosition(fpos);
			boom->setName("[BOOMERANG]");
			getParentLayer()->addObject(boom);
			break;
	}

}

void Player::moveLeft()
{
	defending = false;
	if (state != PLYR_MVG_LEFT)
	{
		state = PLYR_MVG_LEFT;
		facingLeft = true;
			for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
		{
			if (!inAir)
				iter->setAnimation("walk"); // set all to walk
			iter->setFlipH(true);
		}
	}
	
	
}

void Player::moveRight()
{
	defending = false;
	
	if (state != PLYR_MVG_RIGHT)
	{
		facingLeft = false;
		state = PLYR_MVG_RIGHT;
		for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
		{
			if (!inAir)
				iter->setAnimation("walk");
			iter->setFlipH(false);
		}
		
	}
	

}

void Player::stopMoveRight()
{	
	if (!flying)
	{
		if (state == PLYR_MVG_RIGHT)
		{
			if (!inAir)
			{
				for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
				{
					iter->setAnimation("default");
				}
			}
	
			state = PLYR_STANDING;
		}
	}

}

void Player::stopMoveLeft()
{
	if (!flying)
	{
		if (state == PLYR_MVG_LEFT)
		{
			if (!inAir)
			{
				for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
				{
					iter->setAnimation("default");
				}
			}
			state = PLYR_STANDING;
		}
	}

}

void Player::duck()
{
	if (standingOnOneWay) // fall through one way
	{
		inAir = true;
		ignorePlatform = lastOneWay;
	}
}

void Player::resetAnimation()
{
	if (state == PLYR_STANDING) // used to reset all sprites
	{
		for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
		{
			iter->setAnimation("default");
		}
	}
	else
	{
		for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
		{
			iter->setAnimation("walk");
		}
	}

	sprites[CH_SPYRO].setRate(SPYRO_ANIMSPD);
}
void Player::switchCharacter(int character)
{
	SDL_Rect bbox;
	int oldh = getBoundingBox().h;
	switch (character)
	{
	case CH_SPYRO: // switch character and update bounding box / character flags
		flying = false;
		currentCharacter = CH_SPYRO;
		bbox.x = bbox.y = 0;
		bbox.w = SPYRO_WIDTH;
		bbox.h = SPYRO_HEIGHT;
		setBoundingBox(bbox);
		break;
	case CH_LINK:
		if (flying){
			flying = false;
			inAir = true;	
		}
		currentCharacter = CH_LINK;
		bbox.x = 0;
		bbox.y = 0;
		bbox.w = LINK_WIDTH;
		bbox.h = LINK_HEIGHT;
		setBoundingBox(bbox);
		break;
	case CH_MARIO:
		if (flying){
			flying = false;
			inAir = true;
		}
		currentCharacter = CH_MARIO;
		bbox.x = bbox.y = 0;
		bbox.w = MARIO_WIDTH;
		bbox.h = MARIO_HEIGHT;
		setBoundingBox(bbox);
		break;
	}

	//if (oldh < bbox.h)
	position.y -= bbox.h - oldh;

	// flip sprite if we are link or we are facing left, but not both
	sprites[currentCharacter].setFlipH(facingLeft);
}

void Player::hurt(int dmg)
{
	if (invulnTimer <= 0.) // if not in invuln frames
	{
		if (defending) // if link is defending
		{
			invulnTimer = PLAYER_INVULN_TIME;
			health -= dmg/2;
		} 
		else
		{
			Mix_PlayChannel(-1, sfx[SFX_DMG], 0);
			invulnTimer = PLAYER_INVULN_TIME;
			health -= dmg;
		}
		if (health <= 0)
			die();
	}

	
}

void Player::die()
{
	// TODO
	//health = PLAYER_MAXHEALTH;
		// play death screen

	DeathScreen* ds = new DeathScreen(getParentLayer()->getParent());
	getParentLayer()->getParent()->getManager()->addScreen(ds);
}
void Player::resetBBox(){
	SDL_Rect bbox;

	switch (currentCharacter)
	{
	case CH_SPYRO:
		bbox.x = bbox.y = 0;
		bbox.w = SPYRO_WIDTH;
		bbox.h = SPYRO_HEIGHT;
		setBoundingBox(bbox);
		break;
	case CH_LINK:
		
		bbox.x = 0;
		bbox.y = 0;
		bbox.w = LINK_WIDTH;
		bbox.h = LINK_HEIGHT;
		setBoundingBox(bbox);
		break;
	case CH_MARIO:
		currentCharacter = CH_MARIO;
		bbox.x = bbox.y = 0;
		bbox.w = MARIO_WIDTH;
		bbox.h = MARIO_HEIGHT;
		setBoundingBox(bbox);
		break;
	}	

}
void Player::switchMode(){
	
	if (currentCharacter == CH_SPYRO) // switch between gliding and flying
	{
		if (inAir){ // Spyro must be in air to switch modes
			if (!flying)
			{
				if (sprites[CH_SPYRO].getAnimation()!= "flying")
				{
					sprites[CH_SPYRO].setAnimation("flying");
					sprites[CH_SPYRO].setRate(7);	
				}
				flying = true;
				state = PLYR_HOVERING;
			}
			else
			{
				flying = false;
	
				if (state == PLYR_FLYING_LEFT)
				{
					state = PLYR_MVG_LEFT;
				}
				else if (state == PLYR_FLYING_RIGHT)
				{
					state = PLYR_MVG_RIGHT;
				}
				else if (state == PLYR_HOVERING || state == PLYR_FLYING_UP || state == PLYR_FLYING_DOWN)
				{
					state= PLYR_STANDING;
				}
				canJump = false;
				sprites[CH_SPYRO].setAnimation("gliding");		
			}
				
		}
	}
}	
void Player::defend()
{	
	SDL_Rect bbox;
	if (currentCharacter == CH_LINK)
	{
		
		if (facingLeft){ // set bounding box
			bbox.x = -15;
			bbox.y = 0;
			bbox.w = 25;
			bbox.h = LINK_HEIGHT;
			setBoundingBox(bbox);	
		}
		else {
			bbox.x = 10;
			bbox.y = 0;
			bbox.w = 25;
			bbox.h = LINK_HEIGHT;
			setBoundingBox(bbox);
		}
		sprites[currentCharacter].setAnimation("defend");
		defending = true; // set flag
		
	}
}
void Player::land()
{
	if (flying){
		flying = false;
		inAir = false;
		if (velocity.x >5)
		{
		 	defending = false;
			if (state != PLYR_MVG_RIGHT)
			{
				state = PLYR_MVG_RIGHT;
				for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
				{
					iter->setAnimation("walk");
				}
			}
		}
		else if(velocity.x < -5)
		{
			defending = false;
			if (state != PLYR_MVG_LEFT)
			{
				facingLeft = false;
				state = PLYR_MVG_LEFT;
				for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
				{
					iter->setAnimation("walk");
				}
			
			}
		}
		else
		{
			velocity.x = 0;
			for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
			{
				iter->setAnimation("default");
			}
			state = PLYR_STANDING;
		}
	}
}
void Player::flyUp()
{
	if(state != PLYR_FLYING_UP){
		state = PLYR_FLYING_UP;
	}
	
}
void Player::flyDown()
{
	if (state != PLYR_FLYING_DOWN){
		state = PLYR_FLYING_DOWN;
	}
}
void Player::flyLeft()
{

	if (state != PLYR_FLYING_LEFT)
	{
		facingLeft = true;
		state = PLYR_FLYING_LEFT; // set state
		for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
		{
			iter->setFlipH(true);
		}
	}	
	
}
void Player::flyRight()
{
	
	if (state != PLYR_FLYING_RIGHT)
	{
		facingLeft = false;
		state = PLYR_FLYING_RIGHT;
		for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
		{
			iter->setFlipH(false);
		}
	}	
}
void Player::stopFlyUp()
{
	if (state == PLYR_FLYING_UP) {
		if (velocity.x >0)
			flyRight();
		else if (velocity.x < 0)
			flyLeft();
		else{
			state = PLYR_HOVERING;
		}
		velocity.y = 0;
	}
}
void Player::stopFlyDown()
{
	velocity.y = 0;
	if (state == PLYR_FLYING_DOWN){
		if (velocity.x >0)
			flyRight();
		else if (velocity.x < 0)
			flyLeft();
		else{
			state = PLYR_HOVERING;
		}
	}
}
void Player::stopFlyLeft()
{
	velocity.x = 0;
	if (state == PLYR_FLYING_LEFT){
		if (velocity.y >20)
			flyDown();
		else if (velocity.y < -20)
			flyUp();
		else{
			state = PLYR_HOVERING;
		}

	}
	
}
void Player::stopFlyRight()
{
	velocity.x = 0;
	if (state == PLYR_FLYING_RIGHT){
		if (velocity.y >20)
			flyDown();
		else if (velocity.y < -20)
			flyUp();
		else{
			state = PLYR_HOVERING;
		}

	}
}
