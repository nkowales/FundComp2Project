/*
 * HammerBro.h
 *
 *  Created on: Apr 21, 2015
 *      Author: mtroy2
 *
 *      Enemy called HammerBro.  It attacks by throwing Hammers at the player.
 */


#ifndef HAMMERBRO_H_
#define HAMMERBRO_H_

#include "Enemy.h"
#include <cstdlib>
#include <ctime>

#define HAMMERBRO_HEALTH 20
#define HAMMERBRO_WIDTH 16
#define HAMMERBRO_HEIGHT 29
#define HAMMER_COOLDOWN 1.2
#define ANIMATION_TIMER 1.5
#define HAMMERBRO_WALKSPD 50
#define HAMMERBRO_STUNTIMER 1.7

enum HammerBroState
{
	STANDING,
	MVG_RIGHT,
	MVG_LEFT
};
class HammerBro : public Enemy 
{
public:
	HammerBro(Uint32);
	
	void init(ContentManager*);
	void draw(SDL_Renderer*);
	void onWalkIntoWall(WorldObject*, const SDL_Rect&);
	void squish();
	void update(Uint32);
	void walkLeft();
	void walkRight();
	void stop();
	void jump();
	void stun();
	void setProperty(string, string);
private:
	bool sentry = false;
	bool frozen = false;
	int state = STANDING;
	bool facingLeft = false;
	AnimatedTexture sprite;
	void throwHammer();
	bool hasHammer = true;	
	double hammerCooldown = 0;
	double animTimer = ANIMATION_TIMER;
};
#endif
