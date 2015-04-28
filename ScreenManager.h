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

	SDL_Renderer* getRenderer() const;

private:
	ScreenList screens;
	ScreenList screensToAdd;
	ScreenList screensToRemove;
	ContentManager* content = NULL;
	SDL_Renderer* renderer = NULL;
};

#endif /* SCREENMANAGER_H_ */
