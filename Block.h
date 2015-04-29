/*
 * Block.h
 *
 *  Created on: Mar 24, 2015
 *      Author: naiello
 *
 *      Class describing basic platforms in the game.  They are solid to the player and to enemies from all sides.
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
	virtual WorldInput resolveInput(string);

private:
	void kill(WorldObject* = NULL, string = "");
	void enable(WorldObject* = NULL, string = "");
	void disable(WorldObject* = NULL, string = "");
};


#endif /* BLOCK_H_ */
