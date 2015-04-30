/*
 * MainMenuScreen.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: naiello
 */

#include "MainMenuScreen.h"
#include "WorldMap.h"
#include "ScreenManager.h"
#include "MessageBoxScreen.h"

MainMenuScreen::MainMenuScreen() : MenuScreen("Super Legend of Spyro")
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
	WorldMap* world;
	MessageBoxScreen* mbox;
	switch(select)
	{
	case 0:
		world = new WorldMap("Mario-level.tmx", getManager()->getRenderer(), getManager()->getContent());
		getManager()->addScreen(world);
		getManager()->removeScreen(this);
		break;
	case 1:
		mbox = new MessageBoxScreen("Controls",
				"A, D - Move Left, Right (D-Pad L, R)\n"
				"W - Jump (D-Pad Up) \n"
				"S - Fall through floating platforms (D-Pad Down)\n"
				"1, 2, 3 - Switch between Mario, Link and Spyro (Btn. 5, 6, 7)\n"
				"F - Ranged attack (Mario, Link only) (Btn. 3)\n"
				"V - Melee attack (Link, Spyro only) (Btn. 2)\n"
				"J - Toggle Gliding/Flying (Spyro only) (Btn. 8)\n"
				"ESC - Pause Game (Btn. 9)\n\n"

				"TIP: Link's boomerang does minimal damage but will temporarily stun enemies!\n"
				);

		getManager()->addScreen(mbox);
		break;
	case 2:
		mbox = new MessageBoxScreen("About the Game",
				"This game was created for our semester project for Prof. Scott Emrich's Fundamentals of Computing II Class"
				" at the University of Notre Dame (Spring 2015)\n\n"
				"Developers: Nick Aiello, Mitchell Troy, Nathan Kowaleski, Greg Nemecek");
		getManager()->addScreen(mbox);
		//getManager()->removeScreen(this);
		break;
	case 3:
		getManager()->quit();
		break;
	}
}
