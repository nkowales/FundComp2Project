/*
 * Block.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: naiello
 */

#include "Block.h"

Block::Block(Uint32 id) : WorldObject(id)
{
	setCollisionGroup(COLGRP_WORLD);
}

void Block::draw(SDL_Renderer* renderer)
{
	SDL_Rect dst = getBoundingBox();
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
