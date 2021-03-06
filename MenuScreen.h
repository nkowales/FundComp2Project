/*
 * MenuScreen.h
 *
 *  Created on: Apr 27, 2015
 *      Author: naiello
 *
 *      Base class for anything with a selectable menu (main menu, pause menu, etc.)
 */

#ifndef MENUSCREEN_H_
#define MENUSCREEN_H_

#include "Screen.h"
#include <vector>

#define MENU_ITEM_SEP 48
#define MENU_FIRST_ITEM_VPOS 300
#define MENU_FONT_NAME "MenuFont"
#define MENU_FONT_FILE "orange juice 2.0.ttf"
#define MENU_FONT_SIZE 48
#define MENU_ITEM_COLOR { 255, 255, 255, 255 }
#define MENU_SEL_COLOR { 0, 128, 255, 255 }
#define MENU_BG_COLOR { 0, 0, 0, 255}
#define MENU_TITLE_COLOR { 128, 128, 128, 255 }
#define MENU_TITLE_X 10
#define MENU_TITLE_Y (SCREENH - MENU_FONT_SIZE - 10)

struct MenuItem
{
	Texture image;
	Texture selectedImage;
};

class MenuScreen : public Screen
{
public:
	MenuScreen(string);

	virtual void init(ContentManager*);
	virtual void draw(SDL_Renderer*);
	virtual void handleEvent(const SDL_Event&);

protected:
	virtual void addMenuItem(ContentManager*, string);
	virtual void onSelect(int) = 0;
	void setBackColor(SDL_Color);

private:
	vector<MenuItem> menuItems;
	int selected = 0;
	SDL_Color bgColor = MENU_BG_COLOR;
	string title;
	Texture titleTex;
	Mix_Music* music = NULL;
};

#endif /* MENUSCREEN_H_ */
