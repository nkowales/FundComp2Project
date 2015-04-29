/*
 * PauseScreen.cpp
 *
 *  Created on: Apr 29, 2015
 *      Author: naiello
 */

#include "PauseScreen.h"
#include "MainMenuScreen.h"
#include "ScreenManager.h"
PauseScreen::PauseScreen(WorldMap* _cre)
	: MenuScreen("Paused"), creator(_cre)
{

}

void PauseScreen::init(ContentManager* content)
{
	MenuScreen::init(content);
	setBackColor({0, 0, 0, 175});
	addMenuItem(content, "Resume");
	addMenuItem(content, "Quit");
}

void PauseScreen::onSelect(int select)
{
	MainMenuScreen* mmenu = NULL;
	switch (select)
	{
	case 0:
		getManager()->removeScreen(this);
		break;
	case 1:
		mmenu = new MainMenuScreen();
		getManager()->addScreen(mmenu);
		getManager()->removeScreen(this);
		getManager()->removeScreen(creator);
		break;
	}
}

void PauseScreen::handleEvent(const SDL_Event& e)
{
	if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_ESCAPE))
	{
		getManager()->removeScreen(this);
	}
	else
		MenuScreen::handleEvent(e);
}
