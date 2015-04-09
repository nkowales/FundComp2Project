/*
 * Camera.h
 *
 *  Created on: Apr 5, 2015
 *      Author: naiello
 *
 *      Contains basic logic for the scrolling level camera.  Viewport is stored as a rectangle.  transform() method
 *      transforms coordinates or rectangles from level coordinate space (origin at top-left of level) to window coordinate space
 *      (origin at top-left of window).  This is necessary for drawing most WorldObjects, as they occupy a fixed position
 *      in the world, but not a fixed position in the window.  The follow() method determines which WorldObject the camera
 *      should pan to follow.
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <iostream>
#include "Geom.h"

using namespace std;

// Forward declaration of WorldObject
class WorldObject;

class Camera
{
public:
	Camera(int, int, int, int);

	Vector2d transform(const Vector2d&);
	SDL_Rect transform(const SDL_Rect&);
	void update();
	void follow(WorldObject*);
	SDL_Rect getViewport();

private:
	SDL_Rect viewport = {0, 0, 0, 0};
	int lvlWidth = 0;
	int lvlHeight = 0;
	WorldObject* following = NULL;
};

#endif /* CAMERA_H_ */
