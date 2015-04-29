/*
 * Block.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: naiello
 */

#include "Block.h"
#include "ObjectLayer.h"

Block::Block(Uint32 id) : WorldObject(id)
{
	setCollisionGroup(COLGRP_WORLD);
}

void Block::draw(SDL_Renderer* renderer)
{
	/*SDL_Rect dst = getCamera()->transform(getBoundingBox());
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);*/
}

WorldInput Block::resolveInput(string inp)
{
	if (inp == "kill")
		return GET_INPUT_POINTER(&Block::kill);
	else if (inp == "enable")
		return GET_INPUT_POINTER(&Block::enable);
	else if (inp == "disable")
		return GET_INPUT_POINTER(&Block::disable);
	else
		return WorldObject::resolveInput(inp);
}

void Block::kill(WorldObject* sender, string name)
{
	getParentLayer()->removeObject(getId());
}

void Block::enable(WorldObject* sender, string arg)
{
	//enabled = true;
	setCollisionGroup(COLGRP_WORLD);
}

void Block::disable(WorldObject* sender, string arg)
{
	//enabled = false;
	setCollisionGroup(COLGRP_NONE);
}
