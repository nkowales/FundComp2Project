/*
 * DeathScreen.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: naiello
 */

#include "DeathScreen.h"
#include "ScreenManager.h"
#include "MenuScreen.h"

DeathScreen::DeathScreen(WorldMap* _creator)
	: Screen(),
	  creator(_creator)
{
	setOpaque(false);
}

void DeathScreen::init(ContentManager* content)
{
	deathText = content->getTextureFromText("DeathText", "You're dead!", MENU_FONT_NAME, {255, 255, 255, 255});
	deathText.setAlpha(0);
	Mix_HaltMusic();
	deathSound = content->loadMusic("Music/smb_mariodie.wav");
	if (deathSound)
		Mix_PlayMusic(deathSound, 1);
}

void DeathScreen::update(Uint32 time)
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
			deathText.setAlpha(0);
		}
		break;
	case DS_WAIT:
		if (timer <= 0.)
		{
			timer = DS_FADEOUT_TIME;
			state = DS_FADEOUT;
		}

		deathText.setAlpha((Uint8)(255 * ((DS_WAIT_TIME - timer) / DS_WAIT_TIME)));
		break;
	case DS_FADEOUT:
		if (timer <= 0.)
		{
			reset();
		}
		else
		{
			deathText.setAlpha(255);
			alpha = DS_WAITALPHA + ((DS_FADEOUT_TIME - timer) / DS_FADEOUT_TIME) * (1. - DS_WAITALPHA);
		}
		break;
	}

	shade.a = 255 * alpha;

}

void DeathScreen::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, shade.r, shade.g, shade.b, shade.a);
	SDL_RenderFillRect(renderer, NULL);
	deathText.draw(renderer, SCREENW / 3, SCREENH / 2 - 20);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

void DeathScreen::reset()
{
	ScreenManager* manager = getManager();
	string mapname = creator->getMapName();
	manager->removeScreen(creator);

	WorldMap* map = new WorldMap(mapname, manager->getRenderer(), manager->getContent());
	manager->addScreen(map);

	manager->removeScreen(this);
}
