/*
 * MapLayer.h
 *
 *  Created on: Mar 14, 2015
 *      Author: naiello
 *
 *      Abstract base class of all layers in the WorldMap.  Each MapLayer is either a TileLayer or ObjectLayer, and WorldMaps
 *      are made up primarily of a list of these layers that are updated and drawn every frame.
 */

#ifndef MAPLAYER_H_
#define MAPLAYER_H_

// Forward declaration of WorldMap
class WorldMap;

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class MapLayer
{
public:
	MapLayer(WorldMap* = 0);
	virtual ~MapLayer();

	virtual void init();
	virtual void update(Uint32);
	virtual void handleEvent(const SDL_Event&);
	virtual void draw(SDL_Renderer*) = 0;

	WorldMap* getParent() const;
	bool isVisible() const;
	Uint8 getOpacity() const;
	void setOpacity(Uint8);
	void setVisible(bool);
	string getName();
	void setName(string);


private:
	WorldMap* parent;
	bool visible;
	Uint8 alpha;
	string name;
};


#endif /* MAPLAYER_H_ */
