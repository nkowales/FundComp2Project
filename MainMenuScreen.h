/*
 * MainMenuScreen.h
 *
 *  Created on: Apr 28, 2015
 *      Author: naiello
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
