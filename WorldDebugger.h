/*
 * WorldDebugger.h
 *
 *  Created on: Apr 1, 2015
 *      Author: naiello
 */

#ifndef WORLDDEBUGGER_H_
#define WORLDDEBUGGER_H_

#include "WorldObject.h"

class WorldDebugger : public WorldObject
{
public:
	WorldDebugger(Uint32);

	virtual WorldInput resolveInput(string);
	void print(WorldObject*, string);
};

#endif /* WORLDDEBUGGER_H_ */
