/*
 * WorldObject.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: naiello
 */

#include "WorldObject.h"
#include "ObjectLayer.h"
#include "WorldMap.h"
#include <climits>

WorldObject::WorldObject()
	: parentLayer(NULL),
	  colGrp(0)
{
	id = getUniqueID();
}

WorldObject::WorldObject(Uint32 oid)
	: id(oid),
	  parentLayer(NULL),
	  colGrp(0)
{

}

WorldObject::~WorldObject() { }

void WorldObject::init() { }
void WorldObject::uninit() { }
void WorldObject::update(Uint32 time)
{
	double secs = time / 1000.;

	// Kinematic updates
	position.x += velocity.x * secs;
	position.y += velocity.y * secs;
}
void WorldObject::draw(SDL_Renderer* r) { }
void WorldObject::handleEvent(const SDL_Event& e) { }
bool WorldObject::canCollideWith(const WorldObject* other) { return false; }
void WorldObject::handleCollision(WorldObject* other, const SDL_Rect& overlap) { }

void WorldObject::linkOutput(string outpName, WorldOutput) { }
WorldInput WorldObject::resolveInput(string inpName) { return NULL; }

Uint32 WorldObject::getId() const { return id; }
ObjectLayer* WorldObject::getParentLayer() const { return parentLayer; }
Vector2d WorldObject::getPosition() const { return position; }
Vector2d WorldObject::getVelocity() const { return velocity; }
Uint32 WorldObject::getCollisionGroup() const { return colGrp; }
string WorldObject::getName() const { return name; }
Camera* WorldObject::getCamera() const { return getParentLayer()->getParent()->getCamera(); }
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
void WorldObject::setParentLayer(ObjectLayer* lyr)
{
	parentLayer = lyr;
}

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

Uint32 WorldObject::getUniqueID()
{
	// Non map defined ID's start from the biggest possible Uint32 and work downward to minimize collision
	// with map-defined ID's
	static Uint32 nextID = UINT_MAX - 1;

	return nextID--;
}
