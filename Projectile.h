/*
 * Projectile.h
 *
 *  Created on: Apr 22, 2015
 *      Author: mtroy2
 */

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "WorldObject.h"



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
private:
	
	
};

#endif /* PROJECTILE_H_ */
