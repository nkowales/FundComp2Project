/*
 * ObjectLayer.h
 *
 *  Created on: Mar 18, 2015
 *      Author: naiello
 *
 *      ObjectLayers are one of two kinds of MapLayer.  These are layers of the map that contain a list of WorldObjects
 *      (Player, Block, enemies, etc.) that are updated and drawn every frame (this class also handles collisions
 *      between two objects).
 */

#ifndef OBJECTLAYER_H_
#define OBJECTLAYER_H_

#include <iostream>
#include <map>
#include "MapLayer.h"
#include "WorldObject.h"

using namespace std;

typedef map<Uint32, WorldObject*> ObjectMap;

class ObjectLayer : public MapLayer
{
public:
	ObjectLayer(WorldMap* = NULL);
	~ObjectLayer();

	void init();
	void update(Uint32);
	virtual void draw(SDL_Renderer*);
	virtual void handleEvent(const SDL_Event&);

	WorldObject* getObject(Uint32);
	WorldObject* getByName(string);
	void addObject(WorldObject*);

private:
	bool initialized;
	ObjectMap objects;
};

#endif /* OBJECTLAYER_H_ */
