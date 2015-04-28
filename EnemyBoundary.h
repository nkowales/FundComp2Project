/*
 * EnemyBoundary.h
 *
 *  Created on: April 22, 2015
 *      Author: mytoy
 *
 *      Invisible block that enemies can collide with
	(keeps them from walking off ledges)
 */

#ifndef ENEMYBOUNDARY_H_
#define ENEMYBOUNDARY_H_

#include <iostream>
#include "WorldObject.h"
#include "ObjectLayer.h"
#include "Enemy.h"

using namespace std;

class EnemyBoundary : public WorldObject
{
public:
	EnemyBoundary(Uint32);

};

#endif 
