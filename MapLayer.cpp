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
}

MapLayer::~MapLayer()
{

}

WorldMap* MapLayer::getParent() const
{
	return parent;
}

void MapLayer::update()
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
