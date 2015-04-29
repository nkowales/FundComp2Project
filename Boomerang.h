/*
 * Boomerang.h
 *
 *  Created on: Apr 17, 2015
 *      Author: naiello

 * This is our most complex projectile.
 * Link throws it and, if it hits an enemy, if collides and stuns them
 * It is also used to flip triggers in game
*
 */

#ifndef BOOMERANG_H_
#define BOOMERANG_H_

#define SEGMENTS_PER_CURVE 10
#define BOOMERANG_SIZE 10
#define BOOMERANG_SPEED 400
#define BOOMERANG_RANGE 500
#define BOOMERANG_DELAY 20
#include "Enemy.h"
#include <vector>
#include <cmath>
#include "WorldObject.h"
#include "Projectile.h"
class Boomerang : public Projectile
{
public:
	Boomerang(Uint32);

	void init(ContentManager* content);
	void update(Uint32);
	void draw(SDL_Renderer*);

	void setPath(const Path&);
	void setReturnTarget(WorldObject*);
	bool isReturning();
	bool canCollideWith(const WorldObject*);
	void handleCollision(WorldObject* , const SDL_Rect&);

private:
	Path bezierCurve;
	int currentTarget = 1;
	WorldObject* returnTo = NULL;
	double delay = BOOMERANG_DELAY;
	double soundDelay = .2;
	Vector2d calculateBezierPoint(double, Vector2d, Vector2d, Vector2d, Vector2d);
};

#endif /* BOOMERANG_H_ */
