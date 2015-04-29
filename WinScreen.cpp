/*
 *  WinScreen.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: gnemecek
 */

#include "WinScreen.h"
#include "ScreenManager.h"
#include "MenuScreen.h"

WinScreen::WinScreen(WorldMap* _creator)
	: Screen(),
	  creator(_creator)
{
	setOpaque(false);
}

void WinScreen::init(ContentManager* content)
{
	winText = content->getTextureFromText("WinText", "You win!", MENU_FONT_NAME, {255, 255, 255, 255});
	winText.setAlpha(0);
}

void WinScreen::update(Uint32 time)
{
	double secs = time / 1000.;
	if (timer > 0.)
		timer -= secs;

	//if (timer < 0.)
		//timer = 0.;

	switch (state)
	{
	case DS_FADEIN:
		if (timer <= 0.)
		{
			timer = DS_WAIT_TIME;
			state = DS_WAIT;
		}
		else
		{
			alpha = DS_WAITALPHA * (DS_FADEIN_TIME - timer) / DS_FADEIN_TIME;
			winText.setAlpha(0);
		}
		break;
	case DS_WAIT:
		if (timer <= 0.)
		{
			timer = DS_FADEOUT_TIME;
			state = DS_FADEOUT;
		}

		winText.setAlpha((Uint8)(255 * ((DS_WAIT_TIME - timer) / DS_WAIT_TIME)));
		break;
	case DS_FADEOUT:
		if (timer <= 0.)
		{
			reset();
		}
		else
		{
			winText.setAlpha(255);
			alpha = DS_WAITALPHA + ((DS_FADEOUT_TIME - timer) / DS_FADEOUT_TIME) * (1. - DS_WAITALPHA);
		}
		break;
	}

	shade.a = 255 * alpha;

}

void WinScreen::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, shade.r, shade.g, shade.b, shade.a);
	SDL_RenderFillRect(renderer, NULL);
	winText.draw(renderer, SCREENW / 3, SCREENH / 2 - 20);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

void WinScreen::reset()
{
	ScreenManager* manager = getManager();
	manager->removeScreen(creator);

	MainMenuScreen* mmenu = new MainMenuScreen();
	screens->addScreen(mmenu);

	manager->removeScreen(this);
}
