/*
 * CollisionGroup.h
 *
 *  Created on: Mar 27, 2015
 *      Author: naiello
 */

#ifndef COLLISIONGROUP_H_
#define COLLISIONGROUP_H_

/*
 * Collision groups used by the collision checking engine.  When creating new groups, use powers of 2 so that
 * objects can be members of multiple collision groups by using bitwise OR, e.g.
 * int collisionGroup = COLGRP_WORLD | COLGRP_ONEWAY;
 * for a one-way platform.
 *
 * NOTE: Collision group 0 is for non-solid objects.
 */

enum CollisionGroup
{
	COLGRP_PLAYER = 1,			// The player
	COLGRP_WORLD = 2,			// All platforms in the world
	COLGRP_ENEMY = 4,			// Enemies
	COLGRP_ONEWAY = 8,			// One-way platforms
	COLGRP_PROJECTILE = 16		// Bullets, fireballs, etc.
};

#endif /* COLLISIONGROUP_H_ */
