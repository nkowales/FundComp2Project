/*
 * HammerBro.h
 *
 *  Created on: Apr 21, 2015
 *      Author: mtroy2
 */


#ifndef HAMMERBRO_H_
#define HAMMERBRO_H_

#include "Enemy.h"


#define HAMMERBRO_WALKSPEED 20
#define HAMMERBRO_HEALTH 20
#define HAMMERBRO_WIDTH 16
#define HAMMERBRO_HEIGHT 24
#define HAMMER_COOLDOWN 1.5
#define HAMMER_DAMAGE 30
class HammerBro : public Enemy 
{
public:
	HammerBro(Uint32);
	
	void init(ContentManager*);
	void draw(SDL_Renderer*);
	void onWalkIntoWall(WorldObject*, const SDL_Rect&);
	void squish();
private:
	bool facingLeft = false;
	AnimatedTexture sprite;
	void throwHammer();
	bool hasHammer = true;	
	double hammerCooldown = 0;

};
#endif
