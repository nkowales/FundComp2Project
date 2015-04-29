/*
 * MainMenuScreen.h
 *
 *  Created on: Apr 28, 2015
 *      Author: naiello
 *
 *      Main menu of the game. Provides a play, about, and quit option.
 */

#ifndef MAINMENUSCREEN_H_
#define MAINMENUSCREEN_H_

#include "MenuScreen.h"

class MainMenuScreen : public MenuScreen
{
public:
	MainMenuScreen();

	virtual void init(ContentManager*);
	virtual void onSelect(int);
};

#endif /* MAINMENUSCREEN_H_ */
