/*
 * ProgressBar.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: naiello
 */

#include "ProgressBar.h"

ProgressBar::ProgressBar(int _max)
	: max(_max)
{

}

void ProgressBar::setForeground(SDL_Color col)
{
	fore = col;
}

void ProgressBar::setBackground(SDL_Color col)
{
	back = col;
}

void ProgressBar::setBorder(SDL_Color col)
{
	border = col;
}

void ProgressBar::draw(SDL_Renderer* renderer, SDL_Rect rect, int val)
{
	SDL_Rect fill = rect;
	fill.w *= (double)val / max;

	SDL_SetRenderDrawColor(renderer, back.r, back.g, back.b, back.a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, fore.r, fore.g, fore.b, fore.a);
	SDL_RenderFillRect(renderer, &fill);
	SDL_SetRenderDrawColor(renderer, border.r, border.g, border.b, border.a);
	SDL_RenderDrawRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
