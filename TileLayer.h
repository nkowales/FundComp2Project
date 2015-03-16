/*
 * TileLayer.h
 *
 *  Created on: Mar 14, 2015
 *      Author: naiello
 */

#ifndef TILELAYER_H_
#define TILELAYER_H_

#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include "MapLayer.h"
#include "WorldMap.h"

using namespace std;

class TileLayer : public MapLayer
{
public:
	TileLayer(WorldMap*, vector<Uint32>&);

	virtual void draw(SDL_Renderer*);

	Uint8 getOpacity() const;
	void setOpacity(Uint8);

private:
	vector<Uint32> tiles;

	Uint32 width;
	Uint32 height;
	Uint32 tileSize;
	Uint8 alpha;
};


#endif /* TILELAYER_H_ */
