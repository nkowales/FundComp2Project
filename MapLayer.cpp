/*
 * MapLayer.cpp
 *
 *  Created on: Mar 14, 2015
 *      Author: naiello
 */

#include "MapLayer.h"

MapLayer::MapLayer(WorldMap* map)
{
	parent = map;
	visible = true;
	alpha = 255;
}

MapLayer::~MapLayer()
{

}

WorldMap* MapLayer::getParent() const
{
	return parent;
}

void MapLayer::init()
{

}

void MapLayer::update(Uint32)
{
	// Optionally implemented by derived classes.
}

void MapLayer::setVisible(bool v)
{
	visible = v;
}

bool MapLayer::isVisible() const
{
	return visible;
}

void MapLayer::handleEvent(const SDL_Event& e)
{

}
Uint8 MapLayer::getOpacity() const
{
	return alpha;
}

void MapLayer::setOpacity(Uint8 a)
{
	alpha = a;
}

void MapLayer::setName(string nm)
{
	name = nm;
}

string MapLayer::getName()
{
	return name;
}
