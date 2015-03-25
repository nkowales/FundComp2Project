/*
 * WorldObject.h
 *
 *  Created on: Mar 18, 2015
 *      Author: naiello
 */

#ifndef WORLDOBJECT_H_
#define WORLDOBJECT_H_

#include <iostream>
#include <SDL2/SDL.h>
#include "Geom.h"

using namespace std;

/*
 * WorldObject is the abstract base class for all objects in the game world.  It is contained in an object
 * layer (called the parent layer), which runs the update loop, keeping all objects in the game world up to
 * date.  The methods in this file are called in the following order:
 *
 * 1. init (when object is first added to an initialized object layer)
 * 2. handleEvent
 * 3. TODO: set up collision checking
 * 4. update - update object state based on new information from handleEvent and collision checking
 * 5. draw - draw the object to the screen
 * 6. uninit (when object is removed from an object layer or the parent layer is uninitialized)
 */

// Forward declaration of ObjectLayer
class ObjectLayer;

class WorldObject
{
public:
	WorldObject(Uint32);							// Initializes the object BEFORE it is added to an object layer
	virtual ~WorldObject();							// Runs whenever object is destroyed

	virtual void init();							// Initializes the object AFTER it is added to an object layer
	virtual void uninit();							// Runs whenever object is REMOVED from an object layer
	virtual void update(Uint32);					// Update object's state
	virtual void draw(SDL_Renderer*);				// Draw the object
	virtual void handleEvent(const SDL_Event&);		// Handle events

	Uint32 getId() const;							// Returns the object global id
	ObjectLayer* getParentLayer() const;			// Returns a pointer to the parent layer
	Vector2d getPosition() const;
	Vector2d getVelocity() const;
	SDL_Rect getBoundingBox() const;

	void setPosition(Vector2d);
	void setVelocity(Vector2d);
	void setBoundingBox(SDL_Rect);

	virtual void setProperty(string, string);		// Handles map-defined properties

private:
	Uint32 id;										// Unique map-defined object ID

	ObjectLayer* parentLayer;
	Vector2d position;
	Vector2d velocity;
	SDL_Rect boundingBox;
};


#endif /* WORLDOBJECT_H_ */
