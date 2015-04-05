/*
 * WorldDebugger.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: naiello
 */

#include "WorldDebugger.h"

WorldDebugger::WorldDebugger(Uint32 id)
	: WorldObject(id)
{

}

WorldInput WorldDebugger::resolveInput(string inpName)
{
	if (inpName == "print")
	{
		return GET_INPUT_POINTER(&WorldDebugger::print);
	}

	return WorldObject::resolveInput(inpName);
}

void WorldDebugger::print(WorldObject* sender, string arg)
{
	cout << arg << endl;
}
