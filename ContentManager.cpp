/*
 * ContentManager.cpp
 *
 *  Created on: Mar 15, 2015
 *      Author: naiello
 */

#include "ContentManager.h"

ContentManager::ContentManager(SDL_Renderer* rdr)
{
	renderer = rdr;
}

ContentManager::~ContentManager()
{
	// Free memory associated with all textures
	for (TextureList::iterator iter = textures.begin(); iter != textures.end(); iter++)
	{
		SDL_DestroyTexture(iter->second);
	}

	textures.clear();
}

Texture ContentManager::getTexture(string name)
{
	SDL_Texture* tex = NULL;

	// Check to see if the texture was already loaded
	TextureList::iterator loc = textures.find(name);
	if (loc != textures.end())
	{
		tex = loc->second;
	}
	else
	{
		SDL_Surface* surf = IMG_Load(name.c_str());

		if (surf)
		{
			tex = SDL_CreateTextureFromSurface(renderer, surf);

			SDL_FreeSurface(surf);
			surf = NULL;
			pair<string, SDL_Texture*> keyval(name, tex);
			textures.insert(keyval);
		}
	}

	Texture t(tex);
	return t;
}

AnimatedTexture ContentManager::getAnimatedTexture(string name, int xoffs, int yoffs, int fw, int fh, int spc, int frms, int rate)
{
	SDL_Texture* tex = NULL;

	// Check to see if the texture was already loaded
	TextureList::iterator loc = textures.find(name);
	if (loc != textures.end())
	{
		tex = loc->second;
	}
	else
	{
		SDL_Surface* surf = IMG_Load(name.c_str());

		if (surf)
		{
			tex = SDL_CreateTextureFromSurface(renderer, surf);

			SDL_FreeSurface(surf);
			surf = NULL;
			pair<string, SDL_Texture*> keyval(name, tex);
			textures.insert(keyval);
		}
	}

	AnimatedTexture t(tex, xoffs, yoffs, fw, fh, spc, frms, rate);
	return t;
}
