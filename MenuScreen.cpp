/*
 * MenuScreen.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: naiello
 */

#include "MenuScreen.h"
#include "GameConstants.h"

MenuScreen::MenuScreen(string _title) : Screen(), title(_title)
{

}

void MenuScreen::init(ContentManager* content)
{
	content->loadFont(MENU_FONT_NAME, MENU_FONT_FILE, MENU_FONT_SIZE);
	titleTex = content->getTextureFromText("MENU-TITLE-" + title, title, MENU_FONT_NAME, MENU_TITLE_COLOR);
}

void MenuScreen::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);

	if (bgColor.a < 255)
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_RenderFillRect(renderer, NULL);

	if (bgColor.a < 255)
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

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

	titleTex.draw(renderer, MENU_TITLE_X, MENU_TITLE_Y);
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

void MenuScreen::setBackColor(SDL_Color col)
{
	bgColor = col;
	setOpaque(col.a == 255);
}
