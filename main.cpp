/* main.cpp
created by Nathan Kowaleski
02/18/15 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "WorldIO.h"
#include "ContentManager.h"
#include "WorldMap.h"
#include "ScreenManager.h"
#include "MainMenuScreen.h"

using namespace std;

int main(int argc, char** argv)
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Joystick* gGameController = NULL;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "Failed to init SDL." << endl;
		return 1;
	}

	window = SDL_CreateWindow("Super Legend of Spyro", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREENW, SCREENH, SDL_WINDOW_SHOWN);

	if (!window)
	{
		cout << "Failed to open window." << endl;
		return 2;
	}
	//Check for joysticks
	if( SDL_NumJoysticks() < 1 )
	{
		cout <<"Warning: No joysticks connected!\n";
	}
	else
	{
		//Load joystick
		gGameController = SDL_JoystickOpen( 0 );
		if( gGameController == NULL )
		{
			printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
		}
	}

	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//ContentManager content(renderer);
	//WorldMap world("Mario-level.tmx", renderer);
	ScreenManager* screens = new ScreenManager(renderer);
	MainMenuScreen* mmenu = new MainMenuScreen();
	screens->addScreen(mmenu);

	// Wait for user to press X button on window
	bool quit = false;
	SDL_Event e;
	Uint32 currentUpdate, lastUpdate;
	lastUpdate = currentUpdate = SDL_GetTicks();
	while (!quit)
	{
		if (((currentUpdate = SDL_GetTicks()) - lastUpdate) > 10)
		{
			SDL_SetRenderDrawColor(renderer, 23,111, 179, 255);
			SDL_RenderClear(renderer);
			//world.update(currentUpdate - lastUpdate);
			//world.draw(renderer);
			screens->update(currentUpdate - lastUpdate);
			screens->draw();
			SDL_RenderPresent(renderer);
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
					quit = true;
				else
					screens->handleEvent(e);
					//world.handleEvent(e);
			}

			quit |= screens->isQuitting();
			lastUpdate = currentUpdate;
		}
	}

	delete screens;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_JoystickClose( gGameController );
	gGameController = NULL;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}
