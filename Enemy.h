/*
 * Enemy.h
 *
 *  Created on: Apr 19, 2015
 *      Author: naiello
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#define ENEMY_FEETPOS 5

#include "WorldObject.h"
#include "GameConstants.h"

class Enemy : public WorldObject
{
public:
	Enemy(Uint32);

	virtual bool canCollideWith(const WorldObject*);
	virtual void handleCollision(WorldObject*, const SDL_Rect&);
	virtual void update(Uint32);

	int getContactDamage() const;
	int getHealth() const;
	int getMaxHealth() const;

	virtual void hurt(int);
	virtual void kill();
	virtual void setHealth(int);
	virtual bool isAlive();
	virtual void die();
	virtual void squish();

	virtual void onWalkIntoWall(WorldObject*, const SDL_Rect&);

protected:
	void setContactDamage(int);
	void setMaxHealth(int);

private:
	int contactDamage = 0;
	int health = 100;
	int maxHealth = 100;

	Uint32 framesSinceTouchedGround = 0;
	bool inAir = true;
};

#endif /* ENEMY_H_ */
