/*
 * MapLayer.h
 *
 *  Created on: Mar 14, 2015
 *      Author: naiello
 */

#ifndef MAPLAYER_H_
#define MAPLAYER_H_

// Forward declaration of WorldMap
class WorldMap;

#include <SDL2/SDL.h>


class MapLayer
{
public:
	MapLayer(WorldMap* = 0);
	virtual ~MapLayer();

	virtual void update();
	virtual void draw(SDL_Renderer*) = 0;

	WorldMap* getParent() const;
	bool isVisible() const;

	void setVisible(bool);

private:
	WorldMap* parent;
	bool visible;
};


#endif /* MAPLAYER_H_ */
