/*
 * Block.h
 *
 *  Created on: Mar 24, 2015
 *      Author: naiello
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include <SDL2/SDL.h>
#include <iostream>
#include "WorldObject.h"

class Block : public WorldObject
{
public:
	Block(Uint32);

	virtual void draw(SDL_Renderer*);
};


#endif /* BLOCK_H_ */
