/*
 * Tileset.h
 *
 *  Created on: Mar 14, 2015
 *      Author: naiello
 *
 *      Describes a single tileset used in a Tiled map.  the drawTile method will take a tile ID and draw that tile's n * n cell
 *      on the tileset texture.
 */

#ifndef TILESET_H_
#define TILESET_H_

#include <SDL2/SDL.h>


class Tileset
{
public:
	Tileset(SDL_Texture* = 0, Uint32 = 0, Uint32 = 0, Uint32 = 0, Uint32 = 0, Uint32 = 0, Uint32 = 0);

	void drawTile(SDL_Renderer*, Uint32, int, int, Uint8 = 255) const;
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
