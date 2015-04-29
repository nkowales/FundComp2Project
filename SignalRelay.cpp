/*
 * SignalRelay.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: naiello
 */
#include "SignalRelay.h"

SignalRelay::SignalRelay(Uint32 id)
	: WorldObject(id)
{

}

WorldInput SignalRelay::resolveInput(string inp)
{
	if (inp == "trigger")
		return GET_INPUT_POINTER(&SignalRelay::trigger);
	else
		return WorldObject::resolveInput(inp);
}

void SignalRelay::linkOutput(string outp, WorldOutput ptr)
{
	if (outp.find("onTrigger") != string::npos)
		onTrigger.push_back(ptr);
	else
		WorldObject::linkOutput(outp, ptr);
}

void SignalRelay::trigger(WorldObject* sender, string arg)
{
	for (vector<WorldOutput>::iterator iter = onTrigger.begin(); iter != onTrigger.end(); iter++)
	{
		(*iter)();
	}
}
