/*
 * ObjectLayer.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: naiello
 */

#include "ObjectLayer.h"

ObjectLayer::ObjectLayer(WorldMap* parent) : MapLayer(parent)
{
	initialized = false;
}

ObjectLayer::~ObjectLayer()
{
	// Destroy all objects that we own
	for (ObjectMap::iterator iter = objects.begin(); iter != objects.end(); iter++)
	{
		iter->second->uninit();
		delete iter->second;
	}

	// Clear out the object map
	objects.clear();
}

void ObjectLayer::init()
{
	for (ObjectMap::iterator iter = objects.begin(); iter != objects.end(); iter++)
	{
		iter->second->init();
	}
	initialized = true;
}

void ObjectLayer::update(Uint32 time)
{
	for (ObjectMap::iterator iter = objects.begin(); iter != objects.end(); iter++)
	{
		iter->second->update(time);
	}
}

void ObjectLayer::draw(SDL_Renderer* renderer)
{
	for (ObjectMap::iterator iter = objects.begin(); iter != objects.end(); iter++)
	{
		iter->second->draw(renderer);
	}
}

void ObjectLayer::handleEvent(const SDL_Event& e)
{
	for (ObjectMap::iterator iter = objects.begin(); iter != objects.end(); iter++)
	{
		// TODO: Some sort of event/object filtering here to minimize function calls
		iter->second->handleEvent(e);
	}
}

WorldObject* ObjectLayer::getObject(Uint32 id)
{
	ObjectMap::iterator loc = objects.find(id);
	if (loc != objects.end())
	{
		return (loc->second);
	}

	return NULL;
}

void ObjectLayer::addObject(WorldObject* obj)
{
	if (obj)
	{
		pair<Uint32, WorldObject*> pr(obj->getId(), obj);
		objects.insert(pr);

		if (initialized)
		{
			obj->init();
		}
	}
}
