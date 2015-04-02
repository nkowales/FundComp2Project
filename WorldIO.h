/*
 * WorldIO.h
 *
 *  Created on: Apr 1, 2015
 *      Author: naiello
 */

#ifndef WORLDIO_H_
#define WORLDIO_H_

#include <functional>
#include <iostream>

// Forward declaration of WorldObject
class WorldObject;

// General type for inputs to world objects
typedef std::function<void(void)> WorldOutput;

// Preprocessed event handler
typedef std::function<void(WorldObject*, std::string)> WorldInput;

// Easily return pointers to events
#define GET_INPUT_POINTER(funcname) std::bind((funcname), this, std::placeholders::_1, std::placeholders::_2))

struct WorldIOLink
{
	WorldObject* sender;
	std::string senderOutputName;
	std::string targetObjectName;
	std::string argument;
	std::string targetInputName;
};

#endif /* WORLDIO_H_ */
