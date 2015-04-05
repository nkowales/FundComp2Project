/*
 * OneWayPlatform.cpp
 *
 *  Created on: Apr 4, 2015
 *      Author: naiello
 */

#include "OneWayPlatform.h"

OneWayPlatform::OneWayPlatform(Uint32 id) : Block(id)
{
	setCollisionGroup(COLGRP_ONEWAY);
}
