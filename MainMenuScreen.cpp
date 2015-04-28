/*
 * MainMenuScreen.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: naiello
 */

#include "MainMenuScreen.h"
#include "WorldMap.h"
#include "ScreenManager.h"

MainMenuScreen::MainMenuScreen() : MenuScreen()
{

}

void MainMenuScreen::init(ContentManager* content)
{
	MenuScreen::init(content);

	addMenuItem(content, "Play");
	addMenuItem(content, "How to Play");
	addMenuItem(content, "About");
	addMenuItem(content, "Quit");
}

void MainMenuScreen::onSelect(int select)
{
	switch(select)
	{
	case 0:
		WorldMap* world = new WorldMap("Mario-level.tmx", getManager()->getRenderer());
		getManager()->addScreen(world);
		getManager()->removeScreen(this);
		break;
	}
}
