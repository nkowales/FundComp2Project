/*
 * TriggerArea.h
 *
 *  Created on: Apr 1, 2015
 *      Author: naiello
 *
 *      WorldObject that generates an event when the player touches or leaves it.  Can be used for fading out layers, etc.
 */

#ifndef TRIGGERAREA_H_
#define TRIGGERAREA_H_

#include "WorldObject.h"

using namespace std;

class TriggerArea : public WorldObject
{
public:
	TriggerArea(Uint32);

	virtual void linkOutput(string, WorldOutput);
	virtual bool canCollideWith(const WorldObject*);
	virtual void handleCollision(WorldObject*, const SDL_Rect& overlap);
	virtual void update(Uint32);

private:
	bool playerInside = false;
	bool playerTouchedThisFrame = false;
	WorldOutput onTrigger = NULL;
	WorldOutput onEnter = NULL;
	WorldOutput onLeave = NULL;
};

#endif /* TRIGGERAREA_H_ */
