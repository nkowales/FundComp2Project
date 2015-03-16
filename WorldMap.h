/*
 * WorldMap.h
 *
 *  Created on: Mar 6, 2015
 *      Author: naiello
 */

#ifndef WORLDMAP_H_
#define WORLDMAP_H_

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "ContentManager.h"
#include "Tileset.h"
#include "MapLayer.h"

using namespace std;

// TODO: Copy constructor and operator=
class WorldMap
{
public:
	WorldMap();
	WorldMap(string, ContentManager&);
	~WorldMap();

	void draw(SDL_Renderer*);
	void load(string, ContentManager&);

	const Tileset* resolveTile(Uint32) const;
	void getDimensions(Uint32*, Uint32*) const;
	Uint32 getTileSize() const;

private:
	vector<MapLayer*> layers;
	vector<Tileset> tilesets;
	Uint32 width;				// Map dimensions (in tiles)
	Uint32 height;
	Uint32 tileSize;			// Size of each tile (in px), assumed square

};

#endif /* WORLDMAP_H_ */
