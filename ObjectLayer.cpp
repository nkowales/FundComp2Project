/*
 * ObjectLayer.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: naiello
 */

#include "ObjectLayer.h"
#include "ContentManager.h"
#include "WorldMap.h"
#include "Geom.h"

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
	ContentManager* content = getParent()->getContentManager();
	for (ObjectMap::iterator iter = objects.begin(); iter != objects.end(); iter++)
	{
		iter->second->init(content);
	}
	initialized = true;
}

void ObjectLayer::update(Uint32 time)
{
	for (ObjectMap::iterator iter = objects.begin(); iter != objects.end(); iter++)
	{
		// Check all objects AFTER the current one for collisions (to ensure no double-checking)
		for (ObjectMap::iterator iter2 = iter; iter2 != objects.end(); iter2++)
		{
			bool col1 = false, col2 = false;
			if ((iter->second != iter2->second) &&
					((col1 = iter->second->canCollideWith(iter2->second)) || (col2 = iter2->second->canCollideWith(iter->second))))
			{
				if (!col2)
				{
					// If col1 was set, then the expression for col2 will not be executed, this ensures it will
					col2 = iter2->second->canCollideWith(iter->second);
				}

				SDL_Rect overlap;
				SDL_Rect a = iter->second->getBoundingBox();
				SDL_Rect b = iter2->second->getBoundingBox();
				if (getIntersect(a, b, &overlap))
				{
					if (col1)
						iter->second->handleCollision(iter2->second, overlap);
					if (col2)
						iter2->second->handleCollision(iter->second, overlap);
				}
			}
		}

		// Update the objects
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

WorldObject* ObjectLayer::getByName(string nm)
{
	for (ObjectMap::iterator iter = objects.begin(); iter != objects.end(); iter++)
	{
		if (iter->second->getName() == nm)
			return iter->second;
	}

	return NULL;
}

void ObjectLayer::addObject(WorldObject* obj)
{
	if (obj)
	{
		pair<Uint32, WorldObject*> pr(obj->getId(), obj);
		objects.insert(pr);
		obj->setParentLayer(this);

		if (initialized)
		{
			obj->init(getParent()->getContentManager());
		}
	}
}
