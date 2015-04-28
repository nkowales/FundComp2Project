/*
*	AdvanceLevel.cpp
*	Created on April 28
*	Author : gnemecek
*
*
*/

#include "AdvanceLevel.h"

AdvanceLevel::AdvanceLevel(Uint32 id) : WorldObject(id)
{

	setCollisionGroup(COLGRP_ENEMBOUND);
}
