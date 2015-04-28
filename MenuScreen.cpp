/*
 * MenuScreen.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: naiello
 */

#include "MenuScreen.h"
#include "GameConstants.h"

MenuScreen::MenuScreen() : Screen()
{

}

void MenuScreen::init(ContentManager* content)
{
	content->loadFont(MENU_FONT_NAME, MENU_FONT_FILE, MENU_FONT_SIZE);
}

void MenuScreen::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	int y = MENU_FIRST_ITEM_VPOS;
	int x;
	int tw, th;
	Texture* tex;
	for (int i = 0; i < menuItems.size(); i++)
	{
		tex = (i == selected) ? &(menuItems[i].selectedImage) : &(menuItems[i].image);
		tex->getDimensions(&tw, &th);
		x = (SCREENW - tw) / 2;

		tex->draw(renderer, x, y);

		y += MENU_ITEM_SEP;
	}
}

void MenuScreen::handleEvent(const SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			selected = (selected == 0) ? menuItems.size() - 1 : selected - 1;
			break;
		case SDLK_s:
			selected = (selected == menuItems.size() - 1) ? 0 : selected + 1;
			break;
		case SDLK_RETURN:
			onSelect(selected);
			break;
		}
	}
}

void MenuScreen::addMenuItem(ContentManager* content, string text)
{
	MenuItem mitem;
	mitem.image = content->getTextureFromText(string("MTEXT-" + text), text, MENU_FONT_NAME, MENU_ITEM_COLOR);
	mitem.selectedImage = content->getTextureFromText(string("MSELTEXT-" + text), text, MENU_FONT_NAME, MENU_SEL_COLOR);
	menuItems.push_back(mitem);

}
