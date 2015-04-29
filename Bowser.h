/*
 * Bowser.h
 *
 *  Created on: Apr 22, 2015
 *      Author: mtroy2
 */


#ifndef BOWSER_H_TXT_
#define BOWSER_H_TXT_

#include "Enemy.h"
#include <cstdlib>
#include <ctime>
#define BOWSER_WALKSPEED 15
#define BOWSER_HEALTH 300
#define BOWSER_WIDTH 35
#define BOWSER_HEIGHT 41
#define FIREMAGIC_COOLDOWN 5.0
#define JUMP_COOLDOWN 3.0
#define ANIMATION_TIMER 3.00
#define BOWSER_WALKSPD 20
#define BOWSER_JUMPSPD 100
#define SHELLSPIN_COOLDOWN 10
#define ENRAGED_BOW_WALKSPD 80
#define SHELLSPIN_SPEED 120
#define BOW_STUN_TIMER .5
enum BowserState
{
	BOW_STANDING,
	BOW_MVG_RIGHT,
	BOW_MVG_LEFT
};
class Bowser : public Enemy 
{
public:
	Bowser(Uint32);
	
	void init(ContentManager*);
	void draw(SDL_Renderer*);
	void onWalkIntoWall(WorldObject*, const SDL_Rect&);
	void squish();
	void update(Uint32);
	void walkLeft();
	void walkRight();
	void stop();
	void stun();
	
private:
	//flags
	bool enraged = false; // when low on hp
	bool canJump = true;
	int state = BOW_STANDING;
	bool facingLeft = true;
	AnimatedTexture sprite;
	// attacks
	bool spitFlames();
	bool shellSpin();
	bool jump();	
	// cool downs
	double fireMagicCoolDown = 0;
	double jumpCoolDown = 0;
	double animTimer = ANIMATION_TIMER;
	double shellSpinCoolDown = 0;
	double stunTimer = 0;

};
#endif*/
