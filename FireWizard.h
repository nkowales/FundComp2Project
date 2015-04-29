/*
 * FireWizard.h
 *
 *  Created on: Apr 22, 2015
 *      Author: mtroy2
 *
 *      This class is an enemy called FireWizard.  It attacks with fireballs.
 */


#ifndef FIREWIZARD_H_
#define FIREWIZARD_H_

#include "Enemy.h"
#include <cstdlib>
#include <ctime>
#define FIREWIZARD_WALKSPEED 20
#define FIREWIZARD_HEALTH 20
#define FIREWIZARD_WIDTH 15
#define FIREWIZARD_HEIGHT 37
#define ANIMATION_TIMER 3.00
#define FIREWIZARD_WALKSPD 20
#define MAGIC_COOLDOWN 3.5
#define FIREWIZARD_STUNTIME 1
enum FireWizardState
{
	FW_STANDING,
	FW_MVG_RIGHT,
	FW_MVG_LEFT
};
class FireWizard : public Enemy 
{
public:
	FireWizard(Uint32);
	
	void init(ContentManager*);
	void draw(SDL_Renderer*);
	void onWalkIntoWall(WorldObject*, const SDL_Rect&);
	void update(Uint32);
	void walkLeft();
	void walkRight();
	void stop();
	void squish();
	void doMagic();
	void stun();
private:
	int state = FW_STANDING;
	bool facingLeft = false;
	AnimatedTexture sprite;
	double magicCooldown = MAGIC_COOLDOWN;
	double animTimer = ANIMATION_TIMER;	
	double stunTimer = 0;

};
#endif
