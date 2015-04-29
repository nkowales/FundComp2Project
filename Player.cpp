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
#include "WinScreen.h"

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


	AnimatedTexture marioSprite, spyroSprite, lBlueSprite, linkSprite;
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
	//linkSprite.addAnimation("meleeRight", 263,68,40,35,0,6);
	linkSprite.addAnimation("jump", 1, 216, 56, 23, 0, 1); 
	linkSprite.addAnimation("defend", 1, 144, 56, 24, 0, 1);
	

	sprites.push_back(marioSprite);
	sprites.push_back(linkSprite);
	sprites.push_back(spyroSprite);
	sprites.push_back(lBlueSprite);
}

void Player::update(Uint32 time)
{

	double secs = time / 1000.;
	if (sprites[currentCharacter].getAnimation() == "default"){
		resetBBox();
	}
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

		if (onOffense){
			velocity.x = PLAYER_SHUFFLE_SPEED;
		} else{
			velocity.x = PLAYER_WALK_SPEED;
		}
		break;
	case PLYR_MVG_LEFT:
		if (onOffense){
			velocity.x = -PLAYER_SHUFFLE_SPEED;
		} else{
			velocity.x = -PLAYER_WALK_SPEED;
		}
		break;
	case PLYR_HOVERING:
		velocity.x = 0;
		break;
	case PLYR_FLYING_RIGHT:
		velocity.x = PLAYER_WALK_SPEED;
		break;
	case PLYR_FLYING_LEFT:
		velocity.x = -PLAYER_WALK_SPEED;
		break;
	}

	// Apply gravity, etc.
	if (inAir)
	{
		switch(state)
		{
		case PLYR_FLYING_LEFT:
			if (sprites[CH_SPYRO].getAnimation()!= "flying")
			{
				sprites[CH_SPYRO].setAnimation("flying");
				sprites[CH_SPYRO].setRate(7);	
			}
			velocity.y = 0;
			break;
		case PLYR_FLYING_RIGHT:
			velocity.y = 0;
			break;
		case PLYR_HOVERING:
			velocity.y = 0;		
			break;
		case PLYR_FLYING_UP:
			velocity.y = -PLAYER_WALK_SPEED;
			break;
		case PLYR_FLYING_DOWN:
			velocity.y = PLAYER_WALK_SPEED;
		default:
			break;
		}
		if ( velocity.y > 0 && currentCharacter == CH_SPYRO){
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
				if (sprites[CH_SPYRO].getAnimation()!= "flying")
				{
					sprites[CH_SPYRO].setAnimation("flying");
					sprites[CH_SPYRO].setRate(7);	
				}
				
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
	SDL_Rect bbox = getCamera()->transform(getBoundingBox());
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &bbox);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

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
	
	sprites[CH_LINK].setRate(8);

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
			if (flying && currentCharacter == CH_SPYRO)
				state = PLYR_FLYING_UP;	
			else
				jump();
			break;
		case SDLK_s:
			if (flying && currentCharacter == CH_SPYRO)
				state = PLYR_FLYING_DOWN;
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
		case SDLK_j:
			switchMode(); // switch link from offense to defense
			break;
		case SDLK_k:
			defend();
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
			if (flying)
				state = PLYR_HOVERING;
			else
				canJump = true;
			break;
		case SDLK_f:
			rangedAttack();
			break;
		case SDLK_v:
			meleeAttack();
			break;
		case SDLK_k:
			if (currentCharacter == CH_LINK)
				resetAnimation();
			break;
		case SDLK_s:
			if (flying)	
				state = PLYR_HOVERING;
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
					if (flying && currentCharacter == CH_SPYRO)
						state = PLYR_FLYING_DOWN;
					else
						duck();
				}
				//up press
				else if( e.jaxis.value < -8000 )
				{
					if (flying && currentCharacter == CH_SPYRO)
						state = PLYR_FLYING_UP;	
					else
						jump();
					
					canJump = true;
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

bool Player::canCollideWith(const WorldObject* other)
{
	Uint32 grp = other->getCollisionGroup();
	return ((grp == COLGRP_WORLD) || (grp == COLGRP_ONEWAY) ||
			(grp == COLGRP_PROJECTILE) || (grp == COLGRP_ENEMY) || (grp == COLGRP_ENEMPROJECTILE) || 
			(grp == COLGRP_ADVANCE));
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
		if (feetPos < other->getPosition().y)
			framesSinceTouchedGround = 0;
			flying = false;
		ignorePlatform = NULL;
		if ((feetPos < other->getPosition().y) && (velocity.y > 0) && (overlap.w > 2)) // Landed on it
		{
			flying = false;
			standingOnOneWay = false;
			inAir = false;
			position.y = other->getPosition().y - bbox.h;
			
			resetAnimation();
		}
		else if (overlap.h > overlap.w) // hit from side
		{
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
			velocity.y = velocity.y * -PLAYER_HEAD_ELASTICITY;
		}
		break;
	case COLGRP_ONEWAY:
		if (feetPos < other->getPosition().y)
			framesSinceTouchedGround = 0;

		if ((other != ignorePlatform) && (feetPos < other->getPosition().y) && (velocity.y > 0) && (overlap.h < 5)) // Landed on it
		{
			flying = false;
			lastOneWay = static_cast<OneWayPlatform*>(other);
			ignorePlatform = NULL;
			standingOnOneWay = true;
			inAir = false;
			position.y = other->getPosition().y - bbox.h;
			
			resetAnimation();
		}
		break;
	case COLGRP_PROJECTILE:
			boom = dynamic_cast<Boomerang*>(other);
			if (boom && boom->isReturning())
				hasBoomerang = true;
			break;

	case COLGRP_ENEMY:
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
					else{
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
		break;
		}
	/*case COLGRP_ADVANCE:
		if (currentLevel == LVL_MARIO) {
			ScreenManager* manager = getParentLayer()->getParent()->getManager();
			WorldMap* map = new WorldMap("Link-level.tmx", manager->getRenderer());
			manager->addScreen(map);
			manager->removeScreen(getParentLayer()->getParent());
			currentLevel++;
		} else if (currentLevel == LVL_LINK) {
			ScreenManager* manager = getParentLayer()->getParent()->getManager();
			WorldMap* map = new WorldMap("Spyro-level.tmx", manager->getRenderer());
			manager->addScreen(map)
			manager->removeScreen(getParentLayer()->getParent());
			currentLevel++;
		} else if (currentLevel == LVL_SPYRO) {
			WinScreen* ws = new WinScreen(getParentLayer()->getParent());
                        getParentLayer()->getParent()->getManager()->addScreen(ws);
			currentLevel++;
		} else if (currentLevel == LVL_BOWSER) {
			//WinScreen* ws = new WinScreen(getParentLayer()->getParent());
			//getParentLayer()->getParent()->getManager()->addScreen(ws);
		}
		break;*/
	}
}

void Player::jump()
{
	defending = false;
	if (!inAir && canJump)
	{

		for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
		{
			iter->setAnimation("jump");
		}

		sprites[CH_SPYRO].setRate(8);
		inAir = true;
		canJump = false;

		position.y -= PLAYER_JUMP_TOL;
		if (currentCharacter != CH_SPYRO)
		{
			velocity.y = -PLAYER_JUMP_VEL;
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
			if (onOffense){
				if (facingLeft)
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
	Fireball* fball;
	Boomerang* boom;
	Vector2d fpos;
	string current;
	switch(currentCharacter)
	{
		case CH_MARIO:
			if (fireballCooldown > 0.) break;

			fireballCooldown = FIREBALL_COOLDOWN;

			fball = new Fireball(WorldObject::getUniqueID());

			fpos = {(facingLeft) ? position.x : position.x + MARIO_WIDTH, position.y + MARIO_HEIGHT / 3};
			fball->setPosition(fpos);

			if (facingLeft)
				fball->reverseDirection();

			getParentLayer()->addObject(fball);
			break;
		case CH_SPYRO:
			current = sprites[CH_SPYRO].getAnimation();
			sprites[CH_SPYRO].setAnimation("ranged");
			current = sprites[CH_SPYRO].getAnimation();
			fpos = {(facingLeft) ? position.x : position.x + SPYRO_WIDTH, position.y + SPYRO_HEIGHT / 3};

			break;
		case CH_LBLUE:
			fpos = {(facingLeft) ? position.x : position.x + LBLUE_WIDTH, position.y + LBLUE_HEIGHT / 3};
			break;
		case CH_LINK:
			// Make sure we haven't already thrown
			if (!hasBoomerang) break;
			if (!onOffense) break;
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
			boom->setPath(p);									 // Calculates bezier path from control points
			boom->setReturnTarget(this);						// Return to the player after it completes the path
			boom->setPosition(fpos);
			boom->setName("[BOOMERANG]");
			getParentLayer()->addObject(boom);
			break;
	}
	//cout <<  current << endl;
	
	/*Bullet* bullet = new Bullet(WorldObject::getUniqueID());
	bullet->setPosition(position);
	bullet->setAngle(0.125);
	getParentLayer()->addObject(bullet);*/
}

void Player::moveLeft()
{
	defending = false;
	if (!flying)
	{
		defending = false;
		if (state != PLYR_MVG_LEFT)
		{
			state = PLYR_MVG_LEFT;
			facingLeft = true;
	
			for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
			{
				if (!inAir)
					iter->setAnimation("walk");
				iter->setFlipH(true);
			}
		}
	}
	else
	{
		if (state != PLYR_FLYING_LEFT)
		{
			facingLeft = true;
			state = PLYR_FLYING_LEFT;
			for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
			{
				iter->setFlipH(true);
			}
		}	
	}	
}

void Player::moveRight()
{
	defending = false;
	if (!flying){
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
	else
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
	else
	{
		if (state == PLYR_FLYING_RIGHT)
			state = PLYR_HOVERING;
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
	else 
	{
		if (state == PLYR_FLYING_LEFT)
			state = PLYR_HOVERING;
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
	case CH_SPYRO:
		flying = false;
		onOffense = false;
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
		onOffense = false;
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
		onOffense = false;
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
	//sprites[currentCharacter].setFlipH((currentCharacter == CH_LINK) != facingLeft);
	sprites[currentCharacter].setFlipH(facingLeft);
}

void Player::hurt(int dmg)
{
	if (invulnTimer <= 0.)
	{
		if (defending)
		{
			invulnTimer = PLAYER_INVULN_TIME;
			health -= dmg/2;
		} 
		else
		{
			invulnTimer = PLAYER_INVULN_TIME;
			health -= dmg;
		}
		if (health <= 0)
			die();
	}

	//cout << health << endl;
}

void Player::die()
{
	// TODO
	//health = PLAYER_MAXHEALTH;
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
	if (currentCharacter == CH_LINK){
		if (onOffense){
			onOffense = false;
			defending = false;
			sprites[currentCharacter].changeAnimation("walk", 1, 215, 56, 24, 0, 6);
			sprites[currentCharacter].changeAnimation("default", 1, 107, 56, 24, 0, 1);
			hasBoomerang = false;
		} else {
			onOffense = true;
			sprites[currentCharacter].setRate(25);
			sprites[currentCharacter].changeAnimation("walk",565,24,56,24,0,7);
			sprites[currentCharacter].changeAnimation("default",565,24,56,24,0,1);
			hasBoomerang = true;
	
		}


	}
	else if (currentCharacter == CH_SPYRO)
	{
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
			if (!inAir)
			{
				if (state == PLYR_FLYING_LEFT)
				{
					moveLeft();
				}
				else if (state == PLYR_FLYING_RIGHT)
				{
					moveRight();
				}
				else if (state == PLYR_HOVERING || state == PLYR_FLYING_UP || state == PLYR_FLYING_DOWN)
				{
					sprites[CH_SPYRO].setAnimation("default");
				}
			}
			else 
			{
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
		if (!onOffense){
			if (facingLeft){
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
			defending = true;
		}
	}
}

