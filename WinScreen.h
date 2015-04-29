/*
 * WinScreen.h
 *
 *  Created on: Apr 28, 2015
 *      Author: gnemecek
 */

#ifndef WINSCREEN_H_
#define WINSCREEN_H_

#include "Screen.h"
#include "WorldMap.h"

#define DS_SHADE_COLOR { 0, 0, 0, 0 }
#define DS_FADEIN_TIME 1.2
#define DS_WAIT_TIME 2.0
#define DS_FADEOUT_TIME 8.0
#define DS_WAITALPHA 0.6

enum WinScreenState
{
	DS_FADEIN,
	DS_WAIT,
	DS_FADEOUT
};

class WinScreen : public Screen
{
public:
	WinScreen(WorldMap*);

	virtual void init(ContentManager*);
	virtual void draw(SDL_Renderer*);
	virtual void update(Uint32);

private:
	WorldMap* creator = NULL;
	SDL_Color shade = DS_SHADE_COLOR;
	double timer = DS_FADEIN_TIME;
	int state = DS_FADEIN;
	float alpha = 0.;
	Texture winText;

	void reset();
};

#endif /* WINSCREEN_H_ */
