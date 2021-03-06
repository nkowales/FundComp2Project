/*
 * Bowser.h
 *
 *  Created on: Apr 22, 2015
 *      Author: mtroy2
 * This is the class that controls Bowser, the final boss. It contains some
 * Of his specific moves, such as shell spin
 */


#ifndef BOWSER_H_
#define BOWSER_H_


#include "Enemy.h"
#include <cstdlib>
#include <ctime>
#define BOWSER_HEALTH 300
#define BOWSER_WIDTH 35
#define BOWSER_HEIGHT 41
#define BOW_JMPSPD 100
#define ANIMATION_TIMER 3.00
#define BOWSER_WALKSPD 80
#define BOWSER_JUMPSPD 100
#define ENRAGED_BOW_WALKSPD 140
#define SHELLSPIN_SPEED 200
#define BOW_STUN_TIMER .5
#define BOW_ATK_TIMER 2
enum BowserState
{
	BOW_STANDING,
	BOW_MVG_RIGHT,
	BOW_MVG_LEFT,
	BOW_IN_AIR,
	BOW_ATK
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
	int state = BOW_STANDING;
	bool facingLeft = true;
	AnimatedTexture sprite;
	// attacks
	bool spitFlames();
	bool shellSpin();
	bool jump();
	void spawnEnem();	
	// cool downs
	double fireMagicCoolDown = 0;
	double jumpCoolDown = 0;
	double animTimer = ANIMATION_TIMER;
	double shellSpinCoolDown = 0;
	double stunTimer = 0;
	double attackTimer = BOW_ATK_TIMER;
	bool switchState = true;
	bool inAttack = false;


};
#endif
