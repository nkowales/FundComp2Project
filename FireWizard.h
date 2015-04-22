/*
 * Firewizard.h
 *
 *  Created on: Apr 22, 2015
 *      Author: mtroy2
 */


#ifndef FIREWIZARD_H_
#define FIREWIZARD_H_

#include "Enemy.h"
#include <cstdlib>
#include <ctime>
#define FIREWIZARD_WALKSPEED 20
#define FIREWIZARD_HEALTH 20
#define FIREWIZARD_WIDTH 15
#define FIREWIZARD_HEIGHT 32
#define ANIMATION_TIMER 3.00
#define FIREWIZARD_WALKSPD 20
#define MAGIC_COOLDOWN 3.5
enum FireWizardState
{
	STANDING,
	MVG_RIGHT,
	MVG_LEFT
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
private:
	int state = STANDING;
	bool facingLeft = false;
	AnimatedTexture sprite;
	double magicCooldown = MAGIC_COOLDOWN;
	double animTimer = ANIMATION_TIMER;

};
#endif
