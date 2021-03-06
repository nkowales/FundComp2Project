/*
 * Fireball.h
 *
 *  Created on: Apr 12, 2015
 *      Author: naiello
<<<<<<< HEAD
 * Mario's fireball
=======
 *
 *      This class controls the fireballs of Mario and the FireWizard
>>>>>>> 0bac8ae11b5347a63d082ac9c9a7176ae6a823e6
 */

#ifndef FIREBALL_H_
#define FIREBALL_H_

#include "WorldObject.h"
#include "Projectile.h"

#define FIREBALL_FRMW 8
#define FIREBALL_FRMH 9
#define FIREBALL_NFRM 4
#define FIREBALL_SPC  3
#define FIREBALL_ANIMSPD 5

#define FIREBALL_SCALE 1.

class Fireball : public Projectile
{
public:
	Fireball(Uint32);

	void init(ContentManager* content);
	void update(Uint32 time);
	void draw(SDL_Renderer*);
	bool canCollideWith(const WorldObject*);
	void handleCollision(WorldObject*, const SDL_Rect&);

	void kill();
	void reverseDirection();
private:
};

#endif /* FIREBALL_H_ */
