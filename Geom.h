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
#include <vector>
#include <SDL2/SDL.h>

template<typename T>
struct Vector2
{
	Vector2(T _x = 0, T _y = 0) { x = _x; y = _y; }
	T x;
	T y;
};

typedef Vector2<double> Vector2d;
typedef Vector2<int> Vector2i;
typedef std::vector<Vector2d> Path;

template<typename T>
Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b)
{
	return Vector2<T>(a.x + b.x, a.y + b.y);
}

template<typename T>
Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b)
{
	return Vector2<T>(a.x - b.x, a.y - b.y);
}

template<typename T>
Vector2<T> operator*(double s, const Vector2<T>& b)
{
	return Vector2<T>(s * b.x, s * b.y);
}

template<typename T>
double distanceSquare(const Vector2<T>& a, const Vector2<T>& b)
{
	T dx = a.x - b.x;
	T dy = a.y - b.y;
	return dx * dx + dy * dy;
}

Vector2d str2vec(std::string str);
bool getIntersect(const SDL_Rect& a, const SDL_Rect& b, SDL_Rect* result);

#endif /* GEOM_H_ */
