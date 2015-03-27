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
	  colGrp(0)
{

}

WorldObject::~WorldObject() { }

void WorldObject::init() { }
void WorldObject::uninit() { }
void WorldObject::update(Uint32 time) { }
void WorldObject::draw(SDL_Renderer* r) { }
void WorldObject::handleEvent(const SDL_Event& e) { }
bool WorldObject::canCollideWith(const WorldObject& other) { return false; }
void WorldObject::handleCollision(WorldObject& other, const SDL_Rect& overlap) { }

Uint32 WorldObject::getId() const { return id; }
ObjectLayer* WorldObject::getParentLayer() const { return parentLayer; }
Vector2d WorldObject::getPosition() const { return position; }
Vector2d WorldObject::getVelocity() const { return velocity; }
Uint32 WorldObject::getCollisionGroup() const { return colGrp; }
string WorldObject::getName() const { return name; }
SDL_Rect WorldObject::getBoundingBox() const
{
	SDL_Rect bbox = boundingBox;
	bbox.x = position.x;
	bbox.y = position.y;
	return bbox;
}

void WorldObject::setPosition(Vector2d p) { position = p; }
void WorldObject::setVelocity(Vector2d v) { velocity = v; }
void WorldObject::setBoundingBox(SDL_Rect bbox) { boundingBox = bbox; }
void WorldObject::setCollisionGroup(Uint32 grp) { colGrp = grp; }
void WorldObject::setName(string nm) { name = nm; }

void WorldObject::setProperty(string key, string val)
{
	// Lower-case the key string
	transform(key.begin(), key.end(), key.begin(), ::tolower);

	if (key == "velocity")
		velocity = str2vec(val);
	else if (key == "name")
		name = val;
}

bool WorldObject::operator==(const WorldObject& other) const
{
	return (id == other.id);
}

bool WorldObject::operator!=(const WorldObject& other) const
{
	return (id != other.id);
}
