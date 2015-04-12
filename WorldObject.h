/*
 * WorldObject.h
 *
 *  Created on: Mar 18, 2015
 *      Author: naiello
 *
 *      Abstract base class for all objects in the world.  Player, Platforms, Enemies, Triggers, etc. (any object inside the map
 *      that needs to be updated, collided, drawn, or handle user input should derive from this class).  All of the above
 *      functionality can be accessed by overloading the appropriate function listed below, these functions are called as
 *      appropriate by the ObjectLayer that contains this WorldObject.
 */

#ifndef WORLDOBJECT_H_
#define WORLDOBJECT_H_

#include <iostream>
#include <algorithm>
#include <SDL2/SDL.h>
#include "Geom.h"
#include "CollisionGroup.h"
#include "WorldIO.h"
#include "Camera.h"
#include "ContentManager.h"

using namespace std;

/*
 * WorldObject is the abstract base class for all objects in the game world.  It is contained in an object
 * layer (called the parent layer), which runs the update loop, keeping all objects in the game world up to
 * date.  The methods in this file are called in the following order:
 *
 * 1. init (when object is first added to an initialized object layer)
 * 2. handleEvent
 * 3. canCollideWith - check if it is possible for this object to collide with another
 * 4. handleCollision - if canCollideWith returns true and the bounding boxes overlap
 * 5. update - update object state based on new information from handleEvent and collision checking
 * 6. draw - draw the object to the screen
 * 7. uninit (when object is removed from an object layer or the parent layer is uninitialized)
 */

// Forward declaration of ObjectLayer
class ObjectLayer;

class WorldObject
{
public:
	WorldObject();
	WorldObject(Uint32);							// Initializes the object BEFORE it is added to an object layer
	virtual ~WorldObject();							// Runs whenever object is destroyed

	virtual void init(ContentManager* content);					// Initializes the object AFTER it is added to an object layer
	virtual void uninit();										// Runs whenever object is REMOVED from an object layer
	virtual void update(Uint32);								// Update object's state
	virtual void draw(SDL_Renderer*);							// Draw the object
	virtual void handleEvent(const SDL_Event&);					// Handle events
	virtual bool canCollideWith(const WorldObject*);			// Check if it is possible for this object to collide with another one
	virtual void handleCollision(WorldObject*, const SDL_Rect&);// Handle a collision with another WorldObject

	virtual void linkOutput(string, WorldOutput);
	virtual WorldInput resolveInput(string);

	Uint32 getId() const;							// Returns the object global id
	ObjectLayer* getParentLayer() const;			// Returns a pointer to the parent layer
	Vector2d getPosition() const;
	Vector2d getVelocity() const;
	SDL_Rect getBoundingBox() const;
	Uint32 getCollisionGroup() const;
	string getName() const;
	Camera* getCamera() const;

	void setPosition(Vector2d);
	void setVelocity(Vector2d);
	void setBoundingBox(SDL_Rect);
	void setCollisionGroup(Uint32);
	void setName(string);
	void setParentLayer(ObjectLayer*);

	virtual void setProperty(string, string);		// Handles map-defined properties

	bool operator==(const WorldObject&) const;
	bool operator!=(const WorldObject&) const;

protected:
	Vector2d position = {0, 0};
	Vector2d velocity = {0, 0};
	SDL_Rect boundingBox = {0, 0, 0, 0};

private:
	string name;
	Uint32 id;										// Unique map-defined object ID

	ObjectLayer* parentLayer;
	Uint32 colGrp;

	static Uint32 getUniqueID();
};


#endif /* WORLDOBJECT_H_ */
