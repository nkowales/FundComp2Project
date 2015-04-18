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
	bbox.w = MARIO_WIDTH;
	bbox.h = MARIO_HEIGHT;
	setBoundingBox(bbox);
	setCollisionGroup(COLGRP_PLAYER);
	setName("PLAYER");
}

void Player::init(ContentManager* content)
{
	// Get the camera to follow the player
	getCamera()->follow(this);


	AnimatedTexture marioSprite, spyroSprite, lBlueSprite, linkSprite;
	// ("name", xpos, ypos, width, height,  pixels in betwen, frames, [framerate])
	marioSprite = content->getAnimatedTexture("sprites/mario.png", 90, 0, 16, 27, 0, 1, 5);
	marioSprite.addAnimation("walk", 90, 0, 16, 27, 1, 3); 
	marioSprite.addAnimation("jump", 142, 0, 16, 28, 0, 1);

	spyroSprite = content->getAnimatedTexture("sprites/Spyro2.png", 3,48,48,40,16,1,2); // 50 41
	//spyroSprite.addAnimation("walk", 6, 297, 50, 40, 14, 9); // was 50 44
	spyroSprite.addAnimation("walk", 12, 297, 48, 40, 10, 9);
	spyroSprite.addAnimation("jump", 10, 985, 63, 50, 0, 5);
	spyroSprite.addAnimation("glide", 325, 990, 63, 50, 0, 4);

	lBlueSprite = content->getAnimatedTexture("sprites/S-littleblue.png", 0,1,49,34,4,7,6);
	lBlueSprite.addAnimation("walk",0,41,55,35,5,8);

	linkSprite = content->getAnimatedTexture("sprites/Link2.png", 3, 69, 20, 24, 0, 1, 8);
	//linkSprite.addAnimation("walk", 1, 215, 32, 24, 0, 6);
	linkSprite.addAnimation("walk", 6, 215, 27, 24, 5, 6);
	linkSprite.addAnimation("ranged", 2, 481, 23, 25, 4, 5);
	linkSprite.addAnimation("melee", 140, 69, 30, 26, 16, 9);
	linkSprite.addAnimation("jump", 103, 215, LINK_WIDTH, LINK_HEIGHT, 0, 1); 

	sprites.push_back(marioSprite);
	sprites.push_back(linkSprite);
	sprites.push_back(spyroSprite);
	sprites.push_back(lBlueSprite);
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
		//velocity.y += ((currentCharacter == CH_SPYRO) ? SPYRO_GRAVITY : GRAVITY) * secs;
		if ( velocity.y > 0 && currentCharacter == CH_SPYRO){
			sprites[CH_SPYRO].setAnimation("glide");
			velocity.y += SPYRO_GRAVITY*secs;
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
	/*L_Rect bbox = getCamera()->transform(getBoundingBox());
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &bbox);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);*/

	Vector2d pos = getCamera()->transform(position);
	/*switch (currentCharacter){
		case CH_MARIO:
			marioSprite.draw(renderer, pos.x, pos.y);
			break;
		case CH_SPYRO:
			spyroSprite.draw(renderer, pos.x, pos.y);
			break;
		case CH_LBLUE:
			lBlueSprite.draw(renderer, pos.x, pos.y);
			break;
		case CH_LINK:
			linkSprite.draw(renderer, pos.x, pos.y);
			break;
			
	}*/
	sprites[currentCharacter].draw(renderer, pos.x, pos.y);
	

	
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
			if (inAir){
				glide();	
			} else{
				jump();
			}
			break;
		case SDLK_s:
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
		case SDLK_v:
			meleeAttack();
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
	int feetPos;
	SDL_Rect bbox = getBoundingBox();
	feetPos = position.y + bbox.h - PLAYER_FEET;
	/*switch(currentCharacter){
		case CH_MARIO:
			feetPos = position.y + MARIO_HEIGHT - PLAYER_FEET;
			break;
		case CH_SPYRO:
			feetPos = position.y + SPYRO_HEIGHT - PLAYER_FEET;
			break;
		case CH_LBLUE:
			feetPos = position.y + LBLUE_HEIGHT - PLAYER_FEET;
			break;
		case CH_LINK:
			feetPos = position.y + LINK_HEIGHT - PLAYER_FEET;
			break;
	}*/
	

	switch (grp)
	{
	case COLGRP_WORLD: // Ordinary platform
		framesSinceTouchedGround = 0;
		ignorePlatform = NULL;
		if ((feetPos < overlap.y) && (velocity.y > 0)) // Landed on it
		{
			standingOnOneWay = false;
			inAir = false;
			/*switch(currentCharacter){
				case CH_MARIO:
					position.y = other->getPosition().y - MARIO_HEIGHT;
					break;
				case CH_SPYRO:
					position.y = other->getPosition().y - SPYRO_HEIGHT;
					break;
				case CH_LBLUE:
					position.y = other->getPosition().y - LBLUE_HEIGHT;
					break;
				case CH_LINK:
					position.y = other->getPosition().y - LINK_HEIGHT;
					break;
			}*/
			position.y = other->getPosition().y - bbox.h;
			
			resetAnimation();
		}
		else if (overlap.h > overlap.w) // hit from side
		{
			if (overlap.x > position.x) // hit walking right
			{
				/*switch(currentCharacter){
					case CH_MARIO:
						position.x = other->getPosition().x - MARIO_WIDTH;
						break;
					case CH_SPYRO:
						position.x = other->getPosition().x - SPYRO_WIDTH;
						break;
					case CH_LBLUE:
						position.x = other->getPosition().x - LBLUE_WIDTH;
						break;
					case CH_LINK:
						position.x = other->getPosition().x - LINK_WIDTH;
						break;
				}*/
				position.x = other->getPosition().x - bbox.w;
				
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
			position.y = other->getPosition().y - bbox.h;
			/*switch(currentCharacter){
				case CH_MARIO:
					position.y = other->getPosition().y - MARIO_HEIGHT;
					break;
				case CH_SPYRO:
					position.y = other->getPosition().y - SPYRO_HEIGHT;
					break;
				case CH_LBLUE:
					position.y = other->getPosition().y - LBLUE_HEIGHT;
					break;
				case CH_LINK:
					position.y = other->getPosition().y - LINK_HEIGHT;
					break;
			}*/
			
			resetAnimation();
		}
		break;
	}
}

void Player::jump()
{
	if (!inAir && canJump)
	{
		/*switch(currentCharacter){
		case CH_MARIO:
			marioSprite.setAnimation("jump");
			break;
		case CH_SPYRO:
			spyroSprite.setAnimation("jump");
			break;
		case CH_LBLUE:
			lBlueSprite.setAnimation("jump");
			break;
		case CH_LINK:
			linkSprite.setAnimation("jump");
			break;
				
		}*/

		for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
		{
			iter->setAnimation("jump");
		}

		sprites[CH_SPYRO].setRate(25);
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
void Player::glide(){
	if (currentCharacter == CH_SPYRO){
		velocity.y = 0;
		sprites[CH_SPYRO].setAnimation("glide");

	} else {}
}
void Player::meleeAttack()
{
	switch(currentCharacter){
		case CH_LINK:
			sprites[CH_LINK].setAnimation("melee");
			SDL_Rect bbox;
			bbox.x = bbox.y = 0;
			bbox.w = 30;
			bbox.h = 26;
			setBoundingBox(bbox);
			break;
		default:
			break;
	}
	// TODO
}

void Player::rangedAttack()
{
	Fireball* fball = new Fireball(WorldObject::getUniqueID());
	Vector2d fpos;
	string current;
	switch(currentCharacter)
	{
		case CH_MARIO:
			fpos = {(facingLeft) ? position.x : position.x + MARIO_WIDTH, position.y + MARIO_HEIGHT / 3};
			break;
		case CH_SPYRO:
			fpos = {(facingLeft) ? position.x : position.x + SPYRO_WIDTH, position.y + SPYRO_HEIGHT / 3};
			break;
		case CH_LBLUE:
			fpos = {(facingLeft) ? position.x : position.x + LBLUE_WIDTH, position.y + LBLUE_HEIGHT / 3};
			break;
		case CH_LINK:
			current = sprites[CH_LINK].getAnimation();
			sprites[CH_LINK].setAnimation("ranged");
			current = sprites[CH_LINK].getAnimation();
			fpos = {(facingLeft) ? position.x : position.x + LINK_WIDTH, position.y + LINK_HEIGHT / 3};
			break;
	}
	cout <<  current << endl;
	sprites[CH_LINK].setAnimation( current );
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
		if (currentCharacter == CH_LBLUE)
		{
			SDL_Rect bbox;
			bbox.x = bbox.y = 0;
			bbox.w = LBLUERUN_WIDTH;
			bbox.h = LBLUERUN_HEIGHT;
			setBoundingBox(bbox);
		}
		for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
		{
			if (!inAir)
				iter->setAnimation("walk");
			iter->setFlipH(currentCharacter != CH_LINK);
		}
	}
}

void Player::moveRight()
{
	if (state != PLYR_MVG_RIGHT)
	{
		facingLeft = false;
		state = PLYR_MVG_RIGHT;

		for (vector<AnimatedTexture>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
		{
			if (!inAir)
				iter->setAnimation("walk");
			iter->setFlipH(currentCharacter == CH_LINK);
		}
			
		/*marioSprite.setAnimation("walk");
		marioSprite.setFlipH(false);
		spyroSprite.setAnimation("walk");
		spyroSprite.setFlipH(false);*/
		if (currentCharacter == CH_LBLUE){
			SDL_Rect bbox;
			bbox.x = bbox.y = 0;
			bbox.w = LBLUERUN_WIDTH;
			bbox.h = LBLUERUN_HEIGHT;
			setBoundingBox(bbox);
		}
		/*linkSprite.setAnimation("walk");
		linkSprite.setFlipH(true);
		lBlueSprite.setAnimation("walk");
		lBlueSprite.setFlipH(false);*/
	}
}

void Player::stopMoveRight()
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

		//marioSprite.setAnimation("default");
		//spyroSprite.setAnimation("default");
		if(currentCharacter == CH_LBLUE){
			SDL_Rect bbox;
			bbox.x = bbox.y = 0;
			bbox.w = LBLUERUN_WIDTH;
			bbox.h = LBLUERUN_HEIGHT;
			setBoundingBox(bbox);			
		}
		//lBlueSprite.setAnimation("default");
		//linkSprite.setAnimation("default");
		state = PLYR_STANDING;
	}
}

void Player::stopMoveLeft()
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
		//marioSprite.setAnimation("default");
		//spyroSprite.setAnimation("default");
		if(currentCharacter == CH_LBLUE)
		{
			SDL_Rect bbox;
			bbox.x = bbox.y = 0;
			bbox.w = LBLUERUN_WIDTH;
			bbox.h = LBLUERUN_HEIGHT;
			setBoundingBox(bbox);			
		}
		//lBlueSprite.setAnimation("default");
		//linkSprite.setAnimation("default");
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
		currentCharacter = CH_SPYRO;
		bbox.x = bbox.y = 0;
		bbox.w = SPYRO_WIDTH;
		bbox.h = SPYRO_HEIGHT;
		setBoundingBox(bbox);
		break;
	case CH_LBLUE:
		currentCharacter = CH_LBLUE;
		bbox.x = bbox.y = 0;
		bbox.w = LBLUE_WIDTH;
		bbox.h = LBLUE_HEIGHT;
		setBoundingBox(bbox);
		break;
	case CH_LINK:
		currentCharacter = CH_LINK;
		bbox.x = bbox.y = 0;
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

	//if (oldh < bbox.h)
	position.y -= bbox.h - oldh;
	sprites[currentCharacter].setFlipH((currentCharacter == CH_LINK) ^ facingLeft);
}
