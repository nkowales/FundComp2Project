/*
 * Tileset.h
 *
 *  Created on: Mar 14, 2015
 *      Author: naiello
 */

#ifndef TILESET_H_
#define TILESET_H_

#include <SDL2/SDL.h>


class Tileset
{
public:
	Tileset(SDL_Texture* = 0, Uint32 = 0, Uint32 = 0, Uint32 = 0, Uint32 = 0, Uint32 = 0, Uint32 = 0);

	void drawTile(SDL_Renderer*, Uint32, int, int) const;
	Uint32 getFirstGid() const;
	Uint32 getTileCount() const;
	Uint32 getBorder() const { return imgBorder; }

private:
	SDL_Texture* image;
	Uint32 tileSize;
	Uint32 tileSpace;			// Space between each tile (in px)
	Uint32 imgBorder;			// Size of border in tilemap image (in px)
	Uint32 tsetWidth;			// Tileset dimensions (in tiles)
	Uint32 tsetHeight;
	Uint32 firstGid;			// First gid of the tileset
	Uint32 nTiles;
};


#endif /* TILESET_H_ */
