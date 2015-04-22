/*
 * HammerBro.h
 *
 *  Created on: Apr 21, 2015
 *      Author: mtroy2
 */


#ifndef HAMMERBRO_H_
#define HAMMERBRO_H_

#include "Enemy.h"
#include <cstdlib>
#include <ctime>
#define HAMMERBRO_WALKSPEED 20
#define HAMMERBRO_HEALTH 20
#define HAMMERBRO_WIDTH 16
#define HAMMERBRO_HEIGHT 29
#define HAMMER_COOLDOWN 1.2
#define ANIMATION_TIMER 3.00
#define HAMMERBRO_WALKSPD 20
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
private:
	int state = STANDING;
	bool facingLeft = false;
	AnimatedTexture sprite;
	void throwHammer();
	bool hasHammer = true;	
	double hammerCooldown = 0;
	double animTimer = ANIMATION_TIMER;

};
#endif
