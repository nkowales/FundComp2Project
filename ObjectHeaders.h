/*
 * ObjectHeaders.h
 *
 *  Created on: Mar 24, 2015
 *      Author: naiello
 */

#ifndef OBJECTHEADERS_H_
#define OBJECTHEADERS_H_

#include <iostream>

#define REGISTER_OBJ_NAME(STRNM, TYPE) if (type == (STRNM)) { return new TYPE(id); }

// Include headers of all classes that derive from WorldObject below this line
#include "WorldObject.h"
#include "Block.h"

using namespace std;

WorldObject* resolveWorldObject(string type, Uint32 id)
{
	// Register new objects here in the following format
	// !! WITHOUT A SEMICOLON !!
	// REGISTER_OBJ_NAME("StringMapName", typename)

	REGISTER_OBJ_NAME("", Block)
	REGISTER_OBJ_NAME("Block", Block)

	return NULL;
}

#endif /* OBJECTHEADERS_H_ */
