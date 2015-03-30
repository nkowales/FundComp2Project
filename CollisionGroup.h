/*
 * CollisionGroup.h
 *
 *  Created on: Mar 27, 2015
 *      Author: naiello
 */

#ifndef COLLISIONGROUP_H_
#define COLLISIONGROUP_H_

enum CollisionGroup
{
	COLGRP_PLAYER,			// The player
	COLGRP_WORLD,			// All platforms in the world
	COLGRP_ENEMY,			// Enemies
	COLGRP_ONEWAY,			// One-way platforms
	COLGRP_PROJECTILE		// Bullets, fireballs, etc.
};

#endif /* COLLISIONGROUP_H_ */
