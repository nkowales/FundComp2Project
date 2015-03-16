/*
 * ContentManager.h
 *
 *  Created on: Mar 15, 2015
 *      Author: naiello
 */

#ifndef CONTENTMANAGER_H_
#define CONTENTMANAGER_H_

#include <map>
#include <string>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Texture.h"

using namespace std;

typedef map<string, SDL_Texture*> TextureList;

class ContentManager
{
public:
	ContentManager(SDL_Renderer*);
	~ContentManager();

	Texture& getTexture(string);

private:
	SDL_Renderer* renderer;
	TextureList textures;
};


#endif /* CONTENTMANAGER_H_ */
