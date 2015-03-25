/*
 * WorldObject.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: naiello
 */

#include "WorldObject.h"

WorldObject::WorldObject(Uint32 oid)
	: id(oid),
	  parentLayer(NULL),
	  position(),
	  velocity(),
	  boundingBox()
{

}

WorldObject::~WorldObject() { }

void WorldObject::init() { }
void WorldObject::uninit() { }
void WorldObject::update(Uint32 time) { }
void WorldObject::draw(SDL_Renderer* r) { }
void WorldObject::handleEvent(const SDL_Event& e) { }

Uint32 WorldObject::getId() const { return id; }
ObjectLayer* WorldObject::getParentLayer() const { return parentLayer; }
Vector2d WorldObject::getPosition() const { return position; }
Vector2d WorldObject::getVelocity() const { return velocity; }
SDL_Rect WorldObject::getBoundingBox() const { return boundingBox; }

void WorldObject::setPosition(Vector2d p) { position = p; }
void WorldObject::setVelocity(Vector2d v) { velocity = v; }
void WorldObject::setBoundingBox(SDL_Rect bbox) { boundingBox = bbox; }

void WorldObject::setProperty(string key, string val)
{
	//TODO: default property assignments
}
