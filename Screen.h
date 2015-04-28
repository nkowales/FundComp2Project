/*
 * Screen.h
 *
 *  Created on: Apr 21, 2015
 *      Author: naiello
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
#include "ContentManager.h"

using namespace std;

// Forward declaration of ScreenManager
class ScreenManager;

class Screen
{
public:
	Screen();
	virtual ~Screen();

	virtual void init(ContentManager*);
	virtual void update(Uint32);
	virtual void handleEvent(const SDL_Event&);
	virtual void draw(SDL_Renderer*) = 0;
	virtual void uninit();

	ScreenManager* getManager() const;
	bool isOpaque() const;

	void setManager(ScreenManager*);
	void setOpaque(bool);

private:
	ScreenManager* manager = NULL;
	bool opaque = true;
};

#endif /* SCREEN_H_ */
