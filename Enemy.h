/*
 * Enemy.h
 *
 *  Created on: Apr 19, 2015
 *      Author: naiello
<<<<<<< HEAD
 * This is a virtual base class that all game enemies derive from
 * It contains usefull functions and members, such as contact damage, that all enemies inherit
=======
 *
 *      Abstract base class for all enemies.
>>>>>>> b176ce73a787eba89524c2ceefae854fe87c891e
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#define ENEMY_FEETPOS 16
#define BOOMERANG_DAMAGE 3

#include "WorldObject.h"
#include "GameConstants.h"
#include "ProgressBar.h"

class Enemy : public WorldObject
{
public:
	Enemy(Uint32);

	virtual bool canCollideWith(const WorldObject*);
	virtual void handleCollision(WorldObject*, const SDL_Rect&);
	virtual void update(Uint32);
	virtual void draw(SDL_Renderer*);
	virtual void stun();
	int getContactDamage() const;
	int getHealth() const;
	int getMaxHealth() const;
	bool getInvuln() const;
	void setInvuln(bool);
	virtual void hurt(int);
	virtual void kill();
	virtual void setHealth(int);
	virtual bool isAlive();
	virtual void die();
	virtual void squish();
	double getStunTimer();
	bool isStunned();
	
	virtual void onWalkIntoWall(WorldObject*, const SDL_Rect&);

protected:
	bool playerIsLeft = true; // assume player starts to left of this enemy
	void setContactDamage(int);
	void setMaxHealth(int);
	void setStunTimer(double);
	
	Uint32 framesSinceTouchedGround = 0;
	bool inAir = false;

private:
	int contactDamage = 0;
	int health = 100;
	int maxHealth = 100;
	ProgressBar healthBar;
	bool invuln = false;
	double stunTimer = 0;
};

#endif /* ENEMY_H_ */
