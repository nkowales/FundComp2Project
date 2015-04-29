/*
 * Projectile.h
 *
 *  Created on: Apr 22, 2015
 *      Author: mtroy2
 *
 *      Base class for all projectiles like Boomerang, Fireball, and Hammer
 */

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "WorldObject.h"
#include <SDL2/SDL_mixer.h>


class Projectile : public WorldObject
{
public:
	Projectile(Uint32);

	virtual void init(ContentManager* content);
	void update(Uint32 time);
	void draw(SDL_Renderer*);
	bool canCollideWith(const WorldObject*);
	void handleCollision(WorldObject*, const SDL_Rect&);

	void kill();
	void reverseDirection();
protected:
	AnimatedTexture sprite;
	int nBounces = 0;
	int maxBounces;
	int hSpeed;
	int vSpeed;
	int size;
	int gravity;
	int damage;
	Mix_Chunk* sound;	
private:
	
		
};

#endif /* PROJECTILE_H_ */
