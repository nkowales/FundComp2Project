/*
 * WorldMap.h
 *
 *  Created on: Mar 6, 2015
 *      Author: naiello
 *
 *      Contains logic for loading a map generated by Tiled.  The map is loaded into a vector of MapLayers, which are either
 *      ObjectLayers or TileLayers.  Each layer is updated every frame.  The WorldMap also keeps track of the Camera for the level.
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
#include "GameConstants.h"
#include "Camera.h"
#include "Screen.h"

using namespace std;

// TODO: Copy constructor and operator=
class WorldMap : public Screen
{
public:
	WorldMap();
	WorldMap(string, SDL_Renderer*, ContentManager*);
	~WorldMap();

	void update(Uint32);
	void draw(SDL_Renderer*);
	void load(string, SDL_Renderer*, ContentManager*);
	void handleEvent(const SDL_Event&);

	const Tileset* resolveTile(Uint32) const;
	void getDimensions(Uint32*, Uint32*) const;
	Uint32 getTileSize() const;
	MapLayer* findLayer(string);
	Camera* getCamera();
	ContentManager* getContentManager() const;
	string getMapName() const;

private:
	vector<MapLayer*> layers;
	vector<Tileset> tilesets;
	Uint32 width = 0;				// Map dimensions (in tiles)
	Uint32 height = 0;
	Uint32 tileSize = 0;			// Size of each tile (in px), assumed square
	Camera* camera = NULL;
	ContentManager* content = NULL;
	string mapname;
};

#endif /* WORLDMAP_H_ */
