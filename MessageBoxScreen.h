/*
 * MessageBoxScreen.h
 *
 *  Created on: Apr 28, 2015
 *      Author: naiello
 *
 *      Message box with customizable text.  Used to display various information in a compact format.
 */

#ifndef MESSAGEBOXSCREEN_H_
#define MESSAGEBOXSCREEN_H_

#include "GameConstants.h"
#include "MenuScreen.h"

#define MBOX_BGCOL  0, 75, 255, 255
#define MBOX_BRCOL  255, 255, 255, 255
#define MBOX_TICOL  255, 255, 255, 255
#define MBOX_TXCOL  255, 255, 255, 255
#define MBOX_CLCOL  50, 50, 50, 150

#define MBOX_X (SCREENW / 6)
#define MBOX_Y (SCREENH / 4)
#define MBOX_W (2 * SCREENW / 3)
#define MBOX_H (SCREENH / 2)

#define MBOX_TIOFFS 10
#define MBOX_TXOFFS 48

#define MBOX_TEXT_FONT_NAME "MboxText"
#define MBOX_TEXT_FONT_FILE "KOMIKAX_.ttf"
#define MBOX_TEXT_FONT_SIZE 12

class MessageBoxScreen : public Screen
{
public:
	MessageBoxScreen(string, string);

	virtual void init(ContentManager*);
	virtual void draw(SDL_Renderer*);
	virtual void handleEvent(const SDL_Event&);

private:
	string title;
	string text;
	Texture titleTex;
	Texture textTex;
};

#endif /* MESSAGEBOXSCREEN_H_ */
