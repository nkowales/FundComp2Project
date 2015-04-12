/*
 * Texture.h
 *
 *  Created on: Mar 15, 2015
 *      Author: naiello
 *
 *      Wrapper class for SDL_Texture*
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <iostream>
#include <SDL2/SDL.h>

class Texture
{
public:
	Texture(SDL_Texture* = NULL);
	virtual ~Texture();

	virtual void draw(SDL_Renderer*, int, int, float = 1., float = 1.);
	virtual void draw(SDL_Renderer*, SDL_Rect*, SDL_Rect*);
	void getDimensions(int*, int*) const;
	SDL_Texture* getImage() const;

private:
	SDL_Texture* image;
	int width;
	int height;
};


#endif /* TEXTURE_H_ */
