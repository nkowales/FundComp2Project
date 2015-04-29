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
		world = new WorldMap("Spyro-level.tmx", getManager()->getRenderer(), getManager()->getContent());
		getManager()->addScreen(world);
		getManager()->removeScreen(this);
		break;
	case 1:
		mbox = new MessageBoxScreen("Controls",
				"A, D - Move Left, Right\nW - Jump (hold to glide with Spyro)\n"
				"S - Fall through floating platforms\n"
				"1, 2, 3 - Switch between Mario, Link and Spyro\n"
				"F - Ranged attack (Mario, Link only)\n"
				"V - Melee attack (Link, Spyro only)\n"
				"J - Toggle Gliding/Flying (Spyro only)\n"
				"ESC - Pause Game\n\n"
				"TIP: Link's boomerang does minimal damage but will temporarily stun enemies!");

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
