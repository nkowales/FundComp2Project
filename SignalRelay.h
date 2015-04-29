/*
 * SignalRelay.h
 *
 *  Created on: Apr 28, 2015
 *      Author: naiello
 *
 *      Relays a group of map outputs.  Most objects can only fire one output per event, so
 *      this allows a group of signals to be sent out.
 */

#ifndef SIGNALRELAY_H_
#define SIGNALRELAY_H_

#include "WorldObject.h"

class SignalRelay : public WorldObject
{
public:
	SignalRelay(Uint32);

	virtual void linkOutput(string, WorldOutput);
	virtual WorldInput resolveInput(string);
	void trigger(WorldObject* = NULL, string = "");

private:
	vector<WorldOutput> onTrigger;
};

#endif /* SIGNALRELAY_H_ */
