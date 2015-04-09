/*
 * Geom.h
 *
 *  Created on: Mar 18, 2015
 *      Author: naiello
 *
 *      Basic data structures and geometric functions used by WorldObject to describe positions, hitboxes, etc.
 */

#ifndef GEOM_H_
#define GEOM_H_

#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>

template<typename T>
struct Vector2
{
	T x;
	T y;
};

typedef Vector2<double> Vector2d;
typedef Vector2<int> Vector2i;

Vector2d str2vec(std::string str);
bool getIntersect(const SDL_Rect& a, const SDL_Rect& b, SDL_Rect* result);

#endif /* GEOM_H_ */
