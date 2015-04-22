/* main.cpp
created by Nathan Kowaleski
02/18/15 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "WorldIO.h"
#include "ContentManager.h"
#include "WorldMap.h"

using namespace std;

int main(int argc, char** argv)
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Joystick* gGameController = NULL;
//	SDL_Surface* gScreenSurface = NULL;
//	SDL_Surface* background = NULL;
//	SDL_Texture* background = NULL;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "Failed to init SDL." << endl;
		return 1;
	}

	window = SDL_CreateWindow("Tilemap Loader", SDL_WINDOWPOS_UNDEFINED,
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

//	gScreenSurface = SDL_GetWindowSurface(window);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//ContentManager content(renderer);
	WorldMap world("Mario-level.tmx", renderer);

	// Load backgorund image
/*	background = IMG_Load("sprites/M-background00.png");
	if (background == NULL) {
		cout << "Unable to load background image." << endl;
	}
	background = SDL_CreateTextureFromSurface(renderer, back);
	if (background == NULL) {
		cout << "Unable to create background texture. " << IMG_GetError() << endl;
	}
	SDL_FreeSurface(back);
	back = NULL;*/

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
			//SDL_RenderCopy(renderer, background, NULL, NULL); // me
			//SDL_BlitSurface(background, NULL, gScreenSurface, NULL); // me
			//SDL_UpdateWindowSurface(window); // me
			world.update(currentUpdate - lastUpdate);
			world.draw(renderer);
			SDL_RenderPresent(renderer);
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
					quit = true;
				else
					world.handleEvent(e);
			}

			lastUpdate = currentUpdate;
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//SDL_FreeSurface(background);
	//SDL_FreeSurface(gScreenSurface);
	//background = NULL;
	IMG_Quit();
	SDL_Quit();
	SDL_JoystickClose( gGameController );
	gGameController = NULL;
	return 0;
}
