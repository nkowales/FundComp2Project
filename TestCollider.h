/*
 * TestCollider.h
 *
 *  Created on: Mar 27, 2015
 *      Author: naiello
 */

#ifndef TESTCOLLIDER_H_
#define TESTCOLLIDER_H_

#include "WorldObject.h"

using namespace std;

class TestCollider : public WorldObject
{
public:
	TestCollider(Uint32);

	virtual bool canCollideWith(const WorldObject&);
	virtual void handleCollision(WorldObject&, const SDL_Rect&);
	virtual void handleEvent(const SDL_Event&);
	virtual void draw(SDL_Renderer*);

	virtual void setProperty(string, string);

private:
	bool useWASD;
	bool isOverlap;
	SDL_Rect overlap;
};

#endif /* TESTCOLLIDER_H_ */
