/*
 * PauseScreen.h
 *
 *  Created on: Apr 29, 2015
 *      Author: naiello
 *
 *      This class controls the pause screen that displays when the user
 *      pauses the game
 */

#ifndef PAUSESCREEN_H_
#define PAUSESCREEN_H_

#include "MenuScreen.h"
#include "WorldMap.h"

class PauseScreen : public MenuScreen
{
public:
	PauseScreen(WorldMap*);

	void init(ContentManager*);
	void onSelect(int);
	void handleEvent(const SDL_Event&);

private:
	WorldMap* creator;
};


#endif /* PAUSESCREEN_H_ */
