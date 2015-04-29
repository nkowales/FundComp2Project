/*
 * ContentManager.cpp
 *
 *  Created on: Mar 15, 2015
 *      Author: naiello
 */

#include "ContentManager.h"
#include <SDL2/SDL_mixer.h>
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
	for (MusicList::iterator iter = soundtrack.begin(); iter != soundtrack.end(); iter++)
	{
		Mix_FreeMusic(iter->second);
	}
	soundtrack.clear();
	fonts.clear();
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
	TTF_Font* font;
	if (font = getFont(keyname))
		return font;

	font = TTF_OpenFont(fontname.c_str(), size);
	if (font)
	{
		pair<string, TTF_Font*> pr(keyname, font);
		fonts.insert(pr);
	}

	return font;
}

Texture ContentManager::getTextureFromText(string rname, string text, string fontnm, SDL_Color col, Uint32 wrap)
{
	SDL_Texture* tex = NULL;

	if (tex = findTexture(rname))
		return tex;

	TTF_Font* font = getFont(fontnm);
	SDL_Surface* surf = NULL;

	if (wrap)
		surf = TTF_RenderText_Blended_Wrapped(font, text.c_str(), col, wrap);
	else
		surf = TTF_RenderText_Blended(font, text.c_str(), col);

	if (surf == NULL)
		return Texture();

	tex = SDL_CreateTextureFromSurface(renderer, surf);

	if (tex == NULL)
		return Texture();

	pair<string, SDL_Texture*> pr(rname, tex);
	textures.insert(pr);

	SDL_FreeSurface(surf);

	return Texture(tex);
}

SDL_Texture* ContentManager::findTexture(string rname)
{
	TextureList::iterator iter = textures.find(rname);
	if (iter != textures.end())
		return iter->second;
	else
		return NULL;
}
Mix_Music* ContentManager::loadMusic(string name, string location)
{
	
	Mix_Music* gameMusic = NULL;
 	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		cout<< "SDL_mixer could not initialize! SDL_mixer Error: "<< Mix_GetError()  << endl;
	}
	gameMusic = Mix_LoadMUS( location );
	if (!gameMusic){
		cout << "Errorr loading music file!\n";
	}
	pair<string, Mix_Music*> pr(name,gameMusic);
	soundtrack.insert(pr);
}
Mix_Music* ContentManager::getMusic(string)
{

}
