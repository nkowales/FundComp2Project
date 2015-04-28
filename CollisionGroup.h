/*
 * CollisionGroup.h
 *
 *  Created on: Mar 27, 2015
 *      Author: naiello
 *
 *      These collision groups are used by the WorldObject::canCollideWith overloads to determine what each object can collide
 *      with.  Each solid WorldObject should call setCollisionGroup in its constructor.
 */

#ifndef COLLISIONGROUP_H_
#define COLLISIONGROUP_H_

enum CollisionGroup
{
	COLGRP_PLAYER,			// The player
	COLGRP_WORLD,			// All platforms in the world
	COLGRP_ENEMY,			// Enemies
	COLGRP_ONEWAY,			// One-way platforms
	COLGRP_PROJECTILE,		// Bullets, fireballs, etc.
	COLGRP_ENEMPROJECTILE,		// Hammers, etc.
	COLGRP_ENEMBOUND		// EnemyBoundary
};

#endif /* COLLISIONGROUP_H_ */
