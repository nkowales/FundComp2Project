/*
 * LayerController.h
 *
 *  Created on: Apr 4, 2015
 *      Author: naiello
 */

#ifndef LAYERCONTROLLER_H_
#define LAYERCONTROLLER_H_

#include "WorldObject.h"

// Forward declaration of MapLayer
class MapLayer;

enum LayerState
{
	SHOWN,
	HIDDEN,
	FADEIN,
	FADEOUT
};

class LayerController : public WorldObject
{
public:
	LayerController(Uint32);

	WorldInput resolveInput(string);
	void init();
	void update(Uint32);

	void hide(WorldObject* = NULL, string = "");
	void show(WorldObject* = NULL, string = "");
	void fadeOut(WorldObject* = NULL, string = "");
	void fadeIn(WorldObject* = NULL, string = "");

	void setProperty(string, string);
private:
	int state = SHOWN;
	MapLayer* targetLayer = NULL;
	string layerName;

	Uint32 minFade = 0;
	Uint32 maxFade = 255;
	Uint32 fadeRate = 25;
};

#endif /* LAYERCONTROLLER_H_ */
