/*
 * Hammer.h
 *
 *  Created on: Apr 21, 2015
 *      Author: mtroy2
 *
 *      This class controls the Hammers thrown by the HammerBro enemy/
 */

#ifndef HAMMER_H_
#define HAMMER_H_

#include "WorldObject.h"


#define HAMMER_HSPEED 80
#define HAMMER_VSPEED -150
#define HAMMER_SIZE 8
#define HAMMER_GRAVITY 285
#define HAMMER_FRMW 20
#define HAMMER_FRMH 20
#define HAMMER_NFRM 8
#define HAMMER_SPC  0
#define HAMMER_ANIMSPD 5
#define HAMMER_DAMAGE 30
#define HAMMER_SCALE 1.

class Hammer : public WorldObject
{
public:
	Hammer(Uint32);
	void init(ContentManager* content);
	void update(Uint32 time);
	void draw(SDL_Renderer*);
	bool canCollideWith(const WorldObject*);
	void handleCollision(WorldObject*, const SDL_Rect&);
	void reverseDirection();
	void kill();
	int getContactDamage();
	int getXVel();
private:
	AnimatedTexture sprite;
	int contactDamage = HAMMER_DAMAGE;
	int delay = 20;

};

#endif /* HAMMER_H_ */
