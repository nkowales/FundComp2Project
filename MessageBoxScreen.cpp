/*
 * MessageBoxScreen.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: naiello
 */

#include "MessageBoxScreen.h"
#include "ScreenManager.h"

MessageBoxScreen::MessageBoxScreen(string _title, string _text)
	: Screen(),
	  title(_title),
	  text(_text)
{
	setOpaque(false);
}

void MessageBoxScreen::init(ContentManager* content)
{
	content->loadFont(MBOX_TEXT_FONT_NAME, MBOX_TEXT_FONT_FILE, MBOX_TEXT_FONT_SIZE);
	// we can assume menu font has already been loaded

	titleTex = content->getTextureFromText("MBOXT-" + title, title, MENU_FONT_NAME, {MBOX_TICOL});
	textTex = content->getTextureFromText("MBOX-" + title + text.substr(10), text, MBOX_TEXT_FONT_NAME, {MBOX_TXCOL}, MBOX_W - MBOX_TIOFFS * 2);
}

void MessageBoxScreen::handleEvent(const SDL_Event& e)
{
	if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_RETURN))
		getManager()->removeScreen(this);
}

void MessageBoxScreen::draw(SDL_Renderer* renderer)
{
	// Shade the screen
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, MBOX_CLCOL);
	SDL_RenderFillRect(renderer, NULL);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

	// Draw background
	SDL_Rect box = {MBOX_X, MBOX_Y, MBOX_W, MBOX_H};
	SDL_SetRenderDrawColor(renderer, MBOX_BGCOL);
	SDL_RenderFillRect(renderer, &box);
	SDL_SetRenderDrawColor(renderer, MBOX_BRCOL);
	SDL_RenderDrawRect(renderer, &box);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Draw title
	titleTex.draw(renderer, MBOX_X + MBOX_TIOFFS, MBOX_Y + MBOX_TIOFFS);

	// Draw text
	textTex.draw(renderer, MBOX_X + MBOX_TIOFFS, MBOX_Y + MBOX_TXOFFS);
}
