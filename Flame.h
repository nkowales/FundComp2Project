/*
 * Flame.h
 *
 *  Created on: Apr 28, 2015
 *      Author: gnemecek
 */

#ifndef FLAME_H_
#define FLAME_H_

#include "Enemy.h"

class Flame : public Enemy
{
public:
	Flame(Uint32);

	void init(ContentManager*);

};

#endif /* FLAME_H_ */
