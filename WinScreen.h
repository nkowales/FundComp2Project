/*
 * WinScreen.h
 *
 *  Created on: Apr 28, 2015
 *      Author: gnemecek
 *
 *      Like the death screen but for winning.
 */

#ifndef WINSCREEN_H_
#define WINSCREEN_H_

#include "Screen.h"
#include "WorldMap.h"

#define WS_SHADE_COLOR { 0, 0, 0, 0 }
#define WS_FADEIN_TIME 1.2
#define WS_WAIT_TIME 2.0
#define WS_FADEOUT_TIME 8.0
#define WS_WAITALPHA 0.6

enum WinScreenState
{
	WS_FADEIN,
	WS_WAIT,
	WS_FADEOUT
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
	SDL_Color shade = WS_SHADE_COLOR;
	double timer = WS_FADEIN_TIME;
	int state = WS_FADEIN;
	float alpha = 0.;
	Texture winText;

	void reset();
};

#endif /* WINSCREEN_H_ */
