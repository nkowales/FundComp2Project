/*
 * Flame.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: gnemecek
 */

#include "Flame.h"

Flame::Flame(Uint32 id) : Enemy(id)
{

}

void Flame::init(ContentManager* content)
{
	setContactDamage(15);		// Damage taken by player for walking into the flame
}

