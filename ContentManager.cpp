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

	// Free memory associated with all fonts
	for (FontList::iterator iter = fonts.begin(); iter != fonts.end(); iter++)
	{
		TTF_CloseFont(iter->second);
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

TTF_Font* ContentManager::getFont(string nm)
{
	FontList::iterator iter = fonts.find(nm);
	if (iter == fonts.end())
		return NULL;
	else
		return iter->second;
}

TTF_Font* ContentManager::loadFont(string keyname, string fontname, int size)
{
	TTF_Font* font = TTF_OpenFont(fontname.c_str(), size);
	if (font)
	{
		pair<string, TTF_Font*> pr(keyname, font);
		fonts.insert(pr);
	}

	return font;
}

TextTexture ContentManager::getTextureFromText(string text, string fontnm, SDL_Color col)
{
	TTF_Font* font = getFont(fontnm);
	SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), col);

	if (surf == NULL)
		return TextTexture();

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

	if (tex == NULL)
		return TextTexture();

	SDL_FreeSurface(surf);
	return TextTexture(tex);
}
