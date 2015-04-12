/*
 * Bullet.h
 *
 *  Created on: Apr 12, 2015
 *      Author: naiello
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "WorldObject.h"

#define BULLET_SIZE 6
#define BULLET_SPEED 1000

class Bullet : public WorldObject
{
public:
	Bullet(Uint32);

	void init(ContentManager*);
	void draw(SDL_Renderer*);
	bool canCollideWith(const WorldObject*);
	void handleCollision(WorldObject*, const SDL_Rect& overlap);

	void setAngle(double);
private:
	double angle = 0.;
	Vector2d endpoint = {0., 0.};
};

#endif /* BULLET_H_ */
