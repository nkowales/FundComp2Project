/*
 * Tileset.cpp
 *
 *  Created on: Mar 14, 2015
 *      Author: naiello
 */

#include "Tileset.h"
#include <iostream>

using namespace std;

Tileset::Tileset(SDL_Texture* tex, Uint32 tsz, Uint32 tspc, Uint32 border, Uint32 tsetw, Uint32 tseth, Uint32 fgid)
{
	image = tex;
	tileSize = tsz;
	imgBorder = border;
	tileSpace = tspc;
	tsetWidth = tsetw;
	tsetHeight = tseth;
	firstGid = fgid;
	nTiles = tsetWidth * tsetHeight;
}

Uint32 Tileset::getFirstGid() const
{
	return firstGid;
}

Uint32 Tileset::getTileCount() const
{
	return nTiles;
}

void Tileset::drawTile(SDL_Renderer* rdr, Uint32 gid, int x, int y, Uint8 alpha) const
{
	SDL_Rect src;
	SDL_Rect dst;

	Uint32 tile = gid - firstGid;

	src.w = src.h = dst.w = dst.h = tileSize;

	dst.x = x * tileSize;
	dst.y = y * tileSize;

	src.x = imgBorder + (tile % tsetWidth) * (tileSize + tileSpace);
	src.y = imgBorder + (tile / tsetWidth) * (tileSize + tileSpace);

	if (alpha != 255)
	{
		SDL_SetTextureAlphaMod(image, alpha);
		SDL_RenderCopy(rdr, image, &src, &dst);
		SDL_SetTextureAlphaMod(image, 255);
	}
	else
	{
		SDL_RenderCopy(rdr, image, &src, &dst);
	}
}
