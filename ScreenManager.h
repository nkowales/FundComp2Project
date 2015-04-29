/*
 * ScreenManager.h
 *
 *  Created on: Apr 21, 2015
 *      Author: naiello
 */

#ifndef SCREENMANAGER_H_
#define SCREENMANAGER_H_

#include <list>
#include "Screen.h"
#include "ContentManager.h"

typedef list<Screen*> ScreenList;

class ScreenManager
{
public:
	ScreenManager(SDL_Renderer*);
	~ScreenManager();

	void update(Uint32);
	void draw();
	void handleEvent(const SDL_Event&);

	void addScreen(Screen*);
	void removeScreen(Screen*);

	bool isQuitting() const;
	void quit();

	SDL_Renderer* getRenderer() const;
	ContentManager* getContent() const;

private:
	ScreenList screens;
	ScreenList screensToAdd;
	ScreenList screensToRemove;
	ContentManager* content = NULL;
	SDL_Renderer* renderer = NULL;

	bool quitting = false;
};

#endif /* SCREENMANAGER_H_ */
