/*
 * ObjectHeaders.h
 *
 *  Created on: Mar 24, 2015
 *      Author: naiello
 *
 *      This file is used by the WorldObject::load function.  Object types in tiled are stored as strings, and as such must
 *      be converted to actual WorldObject instances by the resolveWorldObject function.  New WorldObjects MUST be listed here
 *      in order to be used in Tiled (see comments below).
 */

#ifndef OBJECTHEADERS_H_
#define OBJECTHEADERS_H_

#include <iostream>

#define REGISTER_OBJ_NAME(STRNM, TYPE) if (type == (STRNM)) { return new TYPE(id); }

// Include headers of all classes that derive from WorldObject below this line
#include "WorldObject.h"
#include "Block.h"
#include "TestCollider.h"
#include "PlayerSpawn.h"
#include "TriggerArea.h"
#include "WorldDebugger.h"
#include "LayerController.h"
#include "OneWayPlatform.h"
#include "Goomba.h"
#include "HammerBro.h"
#include "FireWizard.h"
#include "EnemyBoundary.h"
#include "AdvanceLevel.h"
#include "Switch.h"
#include "SignalRelay.h"
#include "JukeBox.h"
#include "Bowser.h"
#include "Flame.h"
#include "HealthMushroom.h"
#include "BowserSpawn.h"
#include "MushroomSpawner.h"
using namespace std;

WorldObject* resolveWorldObject(string type, Uint32 id)
{
	// Register new objects here in the following format
	// !! WITHOUT A SEMICOLON !!
	// REGISTER_OBJ_NAME("StringMapName", typename)

	REGISTER_OBJ_NAME("", Block)
	REGISTER_OBJ_NAME("Block", Block)
	REGISTER_OBJ_NAME("TestCollider", TestCollider)
	REGISTER_OBJ_NAME("PlayerSpawn", PlayerSpawn)
	REGISTER_OBJ_NAME("TriggerArea", TriggerArea)
	REGISTER_OBJ_NAME("WorldDebugger", WorldDebugger)
	REGISTER_OBJ_NAME("LayerController", LayerController)
	REGISTER_OBJ_NAME("OneWay", OneWayPlatform)
	REGISTER_OBJ_NAME("Goomba", Goomba)
	REGISTER_OBJ_NAME("HammerBro", HammerBro)
	REGISTER_OBJ_NAME("FireWizard", FireWizard)
	REGISTER_OBJ_NAME("EnemyBoundary", EnemyBoundary)
	REGISTER_OBJ_NAME("Advance", AdvanceLevel)
	REGISTER_OBJ_NAME("Switch", Switch)
	REGISTER_OBJ_NAME("SignalRelay", SignalRelay)
	REGISTER_OBJ_NAME("JukeBox", JukeBox)
	REGISTER_OBJ_NAME("Bowser", Bowser)
	REGISTER_OBJ_NAME("Flame", Flame)
	REGISTER_OBJ_NAME("Health", HealthMushroom)
	REGISTER_OBJ_NAME("BowserSpawn", BowserSpawn)
	REGISTER_OBJ_NAME("MushroomSpawner", MushroomSpawner)

	return NULL;
}

#endif /* OBJECTHEADERS_H_ */
