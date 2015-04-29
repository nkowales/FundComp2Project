/*
 * Switch.h
 *
 *  Created on: Apr 28, 2015
 *      Author: naiello
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include "WorldObject.h"
#include "Switch.h"

class Switch : public WorldObject
{
public:
	Switch(Uint32);

	virtual void init(ContentManager*);
	virtual bool canCollideWith(const WorldObject*);
	virtual void handleCollision(WorldObject*, const SDL_Rect&);
	virtual void linkOutput(string, WorldOutput);
	virtual void draw(SDL_Renderer*);
private:
	WorldOutput onActivate = NULL;
	AnimatedTexture tex;
	bool activated = false;

	void activate();
};

#endif /* SWITCH_H_ */
