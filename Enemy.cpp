/*
 * Enemy.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: naiello
 */

#include "Enemy.h"
#include "ObjectLayer.h"

Enemy::Enemy(Uint32 id) : WorldObject(id), healthBar(maxHealth)
{
	setCollisionGroup(COLGRP_ENEMY);
	healthBar.setForeground({0, 255, 0, 255});
}

void Enemy::setContactDamage(int dmg)
{
	contactDamage = dmg;
}

int Enemy::getContactDamage() const
{
	return contactDamage;
}

int Enemy::getHealth() const
{
	return health;
}

int Enemy::getMaxHealth() const
{
	return maxHealth;
}

void Enemy::hurt(int dmg)
{
	health -= dmg;

	if (health <= 0)
		die();
}

void Enemy::kill()
{
	health = 0;
}

void Enemy::setHealth(int h)
{
	health = h;
}

void Enemy::setMaxHealth(int mh)
{
	maxHealth = mh;
	healthBar.setMax(mh);
}

bool Enemy::isAlive()
{
	return (health > 0);
}

bool Enemy::canCollideWith(const WorldObject* other)
{
	int colgrp = other->getCollisionGroup();
	return ((colgrp == COLGRP_WORLD) || (colgrp == COLGRP_ONEWAY) || (colgrp == COLGRP_ENEMBOUND) || (colgrp == COLGRP_PROJECTILE));
}

void Enemy::handleCollision(WorldObject* other, const SDL_Rect& overlap)
{
	int colgrp = other->getCollisionGroup();
	SDL_Rect bbox = getBoundingBox();
	int feetPos = position.y + bbox.h - ENEMY_FEETPOS;
	switch (colgrp)
	{
	case COLGRP_WORLD:
		framesSinceTouchedGround = 0;
		if ((feetPos < overlap.y) && (velocity.y > 0))
		{
			inAir = false;
			position.y = other->getPosition().y - bbox.h;
		}
		else if (overlap.h > overlap.w)
		{
			if (overlap.x > position.x)
			{
				//velocity.x = -velocity.x;
				position.x = other->getPosition().x - bbox.w - 1;
			}
			else
			{
				//velocity.x = -velocity.x;
				position.x = other->getPosition().x + other->getBoundingBox().w + 1;
			}

			onWalkIntoWall(other, overlap);
		}
		else if ((velocity.y < 0) && (other->getPosition().y < position.y))// hit our heads
		{
			velocity.y = velocity.y * -0.5;
		}

		break;
	case COLGRP_ONEWAY:
		framesSinceTouchedGround = 0;
		if ((feetPos < overlap.y) && (velocity.y > 0))
		{
			inAir = false;

			position.y = other->getPosition().y - bbox.h;
		}
		break;
	case COLGRP_ENEMBOUND:
		onWalkIntoWall(other, overlap);
		break;
	case COLGRP_PROJECTILE:
		if ((other->getName() == "[BOOMERANG]") && !(stunTimer > 0))
		{
			hurt(BOOMERANG_DAMAGE);
			stun();
		}
	}
}

void Enemy::onWalkIntoWall(WorldObject*, const SDL_Rect& overlap)
{

}

void Enemy::update(Uint32 time)
{
	double secs = time / 1000.;

	if (framesSinceTouchedGround++ > 2)
		inAir = true;

	if (stunTimer > 0.)
		stunTimer -= secs;

	if (inAir)
		velocity.y += GRAVITY * secs;
	else
		velocity.y = 0.;

	WorldObject::update(time);
}

void Enemy::draw(SDL_Renderer* renderer)
{
	if (health < maxHealth)	// draw healthbar
	{
		SDL_Rect bbox = getBoundingBox();
		bbox.y = position.y - 15;
		bbox.h = 5;

		if (stunTimer > 0)
		{
			healthBar.setForeground({255, 255, 0, 255});
			int blink = (int)(stunTimer * 10) % 2;
			if (blink)
				return;
		}
		else
		{
			healthBar.setForeground({0, 255, 0, 255});
		}
		healthBar.draw(renderer, getCamera()->transform(bbox), health);
	}
}

void Enemy::die()
{
	getParentLayer()->removeObject(getId());
}
void Enemy::squish()
{

}
bool Enemy::getInvuln() const{
	return invuln;
}
void Enemy::setInvuln(bool status) {
	invuln = status;
}
void Enemy::stun(){
	
}
void Enemy::setStunTimer(double d)
{
	stunTimer = d;
}
double Enemy::getStunTimer()
{
	return stunTimer;
}
bool Enemy::isStunned()
{
	return (stunTimer > 0.);
}
