/*
 * ObjectLayer.h
 *
 *  Created on: Mar 18, 2015
 *      Author: naiello
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
	void handleEvent(const SDL_Event&);

	WorldObject* getObject(Uint32);
	void addObject(WorldObject*);

private:
	bool initialized;
	ObjectMap objects;
};

#endif /* OBJECTLAYER_H_ */
