/*
 * Screen.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: naiello
 */

#include "Screen.h"

Screen::Screen()
{

}

Screen::~Screen()
{

}

void Screen::init(ContentManager*) { }
void Screen::update(Uint32) { }
void Screen::handleEvent(const SDL_Event&) { }
void Screen::uninit() { }

ScreenManager* Screen::getManager() const
{
	return manager;
}

bool Screen::isOpaque() const
{
	return opaque;
}

void Screen::setManager(ScreenManager* mgr)
{
	manager = mgr;
}

void Screen::setOpaque(bool opq)
{
	opaque = opq;
}
