/*
 * ContentManager.h
 *
 *  Created on: Mar 15, 2015
 *      Author: naiello
 *
 *      Manages loading and unloading textures for the game.  This way if 10 instances of an object load the same texture, only
 *      one copy of the texture is stored in memory.
 */

#ifndef CONTENTMANAGER_H_
#define CONTENTMANAGER_H_

#include <map>
#include <string>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Texture.h"
#include "AnimatedTexture.h"
#include "TextTexture.h"

using namespace std;

typedef map<string, SDL_Texture*> TextureList;
typedef map<string, TTF_Font*> FontList;

class ContentManager
{
public:
	ContentManager(SDL_Renderer*);
	~ContentManager();

	Texture getTexture(string);
	AnimatedTexture getAnimatedTexture(string, int, int, int, int, int, int, int);
	TTF_Font* loadFont(string, string, int);
	TTF_Font* getFont(string);
	TextTexture getTextureFromText(string, string, SDL_Color);

private:
	SDL_Renderer* renderer;
	TextureList textures;
	FontList fonts;
};


#endif /* CONTENTMANAGER_H_ */
