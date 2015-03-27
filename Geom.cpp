/*
 * Geom.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: naiello
 */

#include "Geom.h"
#include <cmath>

Vector2d str2vec(std::string str)
{
	int split = str.find_first_of(',');

	Vector2d v;
	v.x = std::atoi(str.substr(0, split - 1).c_str());
	v.y = std::atoi(str.substr(split + 1, std::string::npos).c_str());

	return v;
}

bool getIntersect(const SDL_Rect& a, const SDL_Rect& b, SDL_Rect* result)
{
										// No overlap if...
	if ((a.x > (b.x + b.w)) ||			// A is entirely to the right of B OR
			((a.x + a.w) < b.x) || 		// A is entirely to the left of B OR
			(a.y > (b.y + b.h)) ||		// A is entirely below B OR
			((a.y + a.h) < b.y))		// A is entirely above B
	{
		return false;
	}

	// There was overlap, so find the rectangle that describes the overlap if necessary
	if (result)
	{
		result->x = std::max(a.x, b.x);
		result->y = std::max(a.y, b.y);
		result->w = std::min(a.x + a.w, b.x + b.w) - result->x;
		result->h = std::min(a.y + a.h, b.y + b.h) - result->y;
	}

	return true;
}
