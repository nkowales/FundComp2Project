/*
 * TestCollider.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: naiello
 */

#include "TestCollider.h"

TestCollider::TestCollider(Uint32 id)
	: WorldObject(id),
	  useWASD(false),
	  isOverlap(false)
{

}

bool TestCollider::canCollideWith(const WorldObject& other)
{
	return true;
}

void TestCollider::handleCollision(WorldObject& other, const SDL_Rect& intersect)
{
	overlap = intersect;
	isOverlap = true;
	//cout << getId() << endl;
}

void TestCollider::draw(SDL_Renderer* renderer)
{
	SDL_Rect bbox = getBoundingBox();
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &bbox);

	if (isOverlap)
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(renderer, &overlap);
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	isOverlap = false;
}

void TestCollider::handleEvent(const SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if ((!useWASD && (e.key.keysym.sym == SDLK_UP)) || (useWASD && (e.key.keysym.sym == SDLK_w)))
			position.y -= 10;
		else if ((!useWASD && (e.key.keysym.sym == SDLK_DOWN)) || (useWASD && (e.key.keysym.sym == SDLK_s)))
			position.y += 10;
		else if ((!useWASD && (e.key.keysym.sym == SDLK_LEFT)) || (useWASD && (e.key.keysym.sym == SDLK_a)))
			position.x -= 10;
		else if ((!useWASD && (e.key.keysym.sym == SDLK_RIGHT)) || (useWASD && (e.key.keysym.sym == SDLK_d)))
			position.x += 10;
	}
}

void TestCollider::setProperty(string key, string val)
{
	if (key == "useWASD")
		useWASD = true;
	else
		WorldObject::setProperty(key, val);
}
