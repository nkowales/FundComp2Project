/*
 * ProgressBar.h
 *
 *  Created on: Apr 20, 2015
 *      Author: naiello
 *
 *      Generic progress bar.  Mostly used for health bars.
 */

#ifndef PROGRESSBAR_H_
#define PROGRESSBAR_H_

#include <SDL2/SDL.h>

class ProgressBar
{
public:
	ProgressBar(int);

	void setForeground(SDL_Color);
	void setBackground(SDL_Color);
	void setBorder(SDL_Color);
	void setMax(int);

	void draw(SDL_Renderer*, SDL_Rect, int);

private:
	int max;
	SDL_Color fore = {255, 255, 255, 255};
	SDL_Color back = {0, 0, 0, 255};
	SDL_Color border = {0, 0, 0, 255};
};

#endif /* PROGRESSBAR_H_ */
