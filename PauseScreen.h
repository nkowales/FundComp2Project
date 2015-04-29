/*
 * PauseScreen.h
 *
 *  Created on: Apr 29, 2015
 *      Author: naiello
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

private:
	WorldMap* creator;
};


#endif /* PAUSESCREEN_H_ */
