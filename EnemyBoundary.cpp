/*
*	EnemyBoundary.cpp
*	Created on April 22
*	Author : mtroy
*
*
*/

#include "EnemyBoundary.h"

EnemyBoundary::EnemyBoundary(Uint32 id) : WorldObject(id)
{

	setCollisionGroup(COLGRP_ENEMBOUND);
}
