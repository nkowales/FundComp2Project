/*
 * ScreenManager.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: naiello
 */

#include "ScreenManager.h"

ScreenManager::ScreenManager(SDL_Renderer* rdr)
{
	content = new ContentManager(rdr);
	renderer = rdr;
}

ScreenManager::~ScreenManager()
{
	if (content)
	{
		delete content;
		content = NULL;
	}

	if (!screens.empty())
	{
		for (ScreenList::iterator iter = screens.begin(); iter != screens.end(); iter++)
		{
			delete *iter;
		}

		screens.clear();
	}
}

void ScreenManager::update(Uint32 time)
{
	for (ScreenList::iterator iter = screensToRemove.begin(); iter != screensToRemove.end(); iter++)
	{
		ScreenList::iterator rmv = find(screens.begin(), screens.end(), *iter);
		if (rmv != screens.end())
		{
			(*rmv)->uninit();
			screens.remove(*rmv);
			delete *rmv;
		}
	}
	for (ScreenList::iterator iter = screensToAdd.begin(); iter != screensToAdd.end(); iter++)
	{
		screens.push_front(*iter);
		(*iter)->setManager(this);
		(*iter)->init(content);
	}

	screensToRemove.clear();
	screensToAdd.clear();
	/*for (ScreenList::iterator iter = screens.begin(); iter != screens.end(); iter++)
	{
		(*iter)->update(time);
	}*/
	screens.front()->update(time);
}

void ScreenManager::draw()
{
	for (ScreenList::reverse_iterator iter = screens.rbegin(); iter != screens.rend(); iter++)
	{
		ScreenList::reverse_iterator iter2 = iter;
		iter2++;

		if ((iter2 != screens.rend()) && (*iter2)->isOpaque())
			continue;

		(*iter)->draw(renderer);
	}
}

void ScreenManager::handleEvent(const SDL_Event& e)
{
	/*for (ScreenList::iterator iter = screens.begin(); iter != screens.end(); iter++)
	{
		(*iter)->handleEvent(e);

		if ((*iter)->isOpaque())
			break;
	}*/
	screens.front()->handleEvent(e);
}

void ScreenManager::addScreen(Screen* scr)
{
	screensToAdd.push_front(scr);
}

void ScreenManager::removeScreen(Screen* scr)
{
	screensToRemove.push_front(scr);
}

SDL_Renderer* ScreenManager::getRenderer() const
{
	return renderer;
}

void ScreenManager::quit()
{
	quitting = true;
}

bool ScreenManager::isQuitting() const
{
	return quitting;
}

ContentManager* ScreenManager::getContent() const
{
	return content;
}
