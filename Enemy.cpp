/*
 * Enemy.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: naiello
 */

#include "Enemy.h"
#include "ObjectLayer.h"

Enemy::Enemy(Uint32 id) : WorldObject(id)
{
	setCollisionGroup(COLGRP_ENEMY);
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
}

bool Enemy::isAlive()
{
	return (health > 0);
}

bool Enemy::canCollideWith(const WorldObject* other)
{
	int colgrp = other->getCollisionGroup();
	return ((colgrp == COLGRP_WORLD) || (colgrp == COLGRP_ONEWAY));
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
				position.x = other->getPosition().x - bbox.x - 1;
			}
			else
			{
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

	if (inAir)
		velocity.y += GRAVITY * secs;
	else
		velocity.y = 0.;

	WorldObject::update(time);
}

void Enemy::die()
{
	getParentLayer()->removeObject(getId());
}
