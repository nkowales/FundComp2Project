/*
 * Camera.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: naiello
 */

#include "Camera.h"
#include "WorldObject.h"

Camera::Camera(int vw, int vh, int lw, int lh)
	: lvlWidth(lw),
	  lvlHeight(lh)
{
	viewport.w = vw;
	viewport.h = vh;
}

void Camera::follow(WorldObject* target)
{
	following = target;
}

void Camera::update()
{
	if (following)
	{
		Vector2d followPos = following->getPosition();
		int widthOver3 = viewport.w / 3;
		int heightOver3 = viewport.h / 3;

		if (followPos.x < viewport.x + widthOver3)
			viewport.x = followPos.x - widthOver3;
		else if (followPos.x > viewport.x + viewport.w - widthOver3)
			viewport.x = followPos.x - 2 * widthOver3;

		if (followPos.y < viewport.y + heightOver3)
			viewport.y = followPos.y - heightOver3;
		else if (followPos.y > viewport.y + viewport.h - heightOver3)
			viewport.y = followPos.y - 2 * heightOver3;

		viewport.x = min(max(viewport.x, 0), lvlWidth - viewport.w);
		viewport.y = min(max(viewport.y, 0), lvlHeight - viewport.h);
	}
}

Vector2d Camera::transform(const Vector2d& v)
{
	Vector2d v2 = {v.x - viewport.x, v.y - viewport.y};
	return v2;
}

SDL_Rect Camera::transform(const SDL_Rect& r)
{
	SDL_Rect t = { r.x - viewport.x, r.y - viewport.y, r.w, r.h };
	return t;
}

SDL_Rect Camera::getViewport()
{
	return viewport;
}
