/*
 * TileLayer.cpp
 *
 *  Created on: Mar 14, 2015
 *      Author: naiello
 */

#include "TileLayer.h"

TileLayer::TileLayer(WorldMap* parent, vector<Uint32>& tlist) : MapLayer(parent)
{
	getParent()->getDimensions(&width, &height);
	tileSize = getParent()->getTileSize();
	tiles = tlist;
}

void TileLayer::draw(SDL_Renderer* renderer)
{
	Uint32 index;
	const Tileset* tset = NULL;
	SDL_Rect viewport = getParent()->getCamera()->getViewport();
	Uint32 x1, x2, y1, y2;
	x1 = viewport.x / tileSize;
	y1 = viewport.y / tileSize;
	x2 = x1 + (viewport.w / tileSize) + 1;
	y2 = y1 + (viewport.h / tileSize) + 1;
	for (Uint32 y = y1; y < y2; y++)
	{
		for (Uint32 x = x1; x < x2; x++)
		{
			// Convert x, y coordinate to an index in the 1 dimensional tile vector.
			index = y * width + x;

			if (tiles[index])
			{
				// Get a pointer to the correct tileset to draw the tile from
				tset = getParent()->resolveTile(tiles[index]);

				if (tset)
				{
					// Source the tile from the correct tileset and draw it
					tset->drawTile(renderer, tiles[index], x * tileSize - viewport.x, y * tileSize - viewport.y, getOpacity());
				}
			}
		}
	}
}
