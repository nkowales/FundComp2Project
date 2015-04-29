/*
 * FireMagic.h
 *
 *  Created on: Apr 21, 2015
 *      Author: mtroy2
 */

#ifndef FIREMAGIC_H_
#define FIREMAGIC_H_

#include "WorldObject.h"


#define FIREMAGIC_SPEED 130
#define FIREMAGIC_SIZE 8
#define FIREMAGIC_GRAVITY 0
#define FIREMAGIC_FRMW 20
#define FIREMAGIC_FRMH 12
#define FIREMAGIC_NFRM 3
#define FIREMAGIC_SPC  0
#define FIREMAGIC_ANIMSPD 5
#define FIREMAGIC_DAMAGE 20
#define FIREMAGIC_SCALE 1.

class FireMagic : public WorldObject
{
public:
	FireMagic(Uint32);
	void init(ContentManager* content);
	void update(Uint32 time);
	void draw(SDL_Renderer*);
	bool canCollideWith(const WorldObject*);
	void handleCollision(WorldObject*, const SDL_Rect&);
	void reverseDirection();
	void kill();
	int getContactDamage();
	void setFlipH(bool);
private:
	AnimatedTexture sprite;
	int contactDamage = FIREMAGIC_DAMAGE;
	int delay = 20;

};

#endif /* FIREMAGIC_H_ */
