/*
 * Boomerang.h
 *
 *  Created on: Apr 17, 2015
 *      Author: naiello
 */

#ifndef BOOMERANG_H_
#define BOOMERANG_H_

#define SEGMENTS_PER_CURVE 10
#define BOOMERANG_SIZE 10
#define BOOMERANG_SPEED 400
#define BOOMERANG_RANGE 500
#define BOOMERANG_DELAY 20

#include <vector>
#include <cmath>
#include "WorldObject.h"

class Boomerang : public WorldObject
{
public:
	Boomerang(Uint32);

	void init(ContentManager* content);
	void update(Uint32);
	void draw(SDL_Renderer*);

	void setPath(const Path&);
	void setReturnTarget(WorldObject*);
	bool isReturning();

private:
	Path bezierCurve;
	AnimatedTexture sprite;
	int currentTarget = 1;
	WorldObject* returnTo = NULL;
	int delay = BOOMERANG_DELAY;

	Vector2d calculateBezierPoint(double, Vector2d, Vector2d, Vector2d, Vector2d);
};

#endif /* BOOMERANG_H_ */
