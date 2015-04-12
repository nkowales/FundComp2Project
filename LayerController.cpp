/*
 * LayerController.cpp
 *
 *  Created on: Apr 4, 2015
 *      Author: naiello
 */

#include "LayerController.h"
#include "ObjectLayer.h"
#include "WorldMap.h"

LayerController::LayerController(Uint32 id)
	: WorldObject(id)
{

}

void LayerController::hide(WorldObject* sender, string arg)
{
	state = HIDDEN;

	if (targetLayer)
		targetLayer->setVisible(false);
}

void LayerController::show(WorldObject* sender, string arg)
{
	state = SHOWN;

	if (targetLayer)
		targetLayer->setVisible(true);
}

void LayerController::fadeIn(WorldObject* sender, string arg)
{
	state = FADEIN;
}

void LayerController::fadeOut(WorldObject* sender, string arg)
{
	state = FADEOUT;
}

void LayerController::init(ContentManager* content)
{
	targetLayer = getParentLayer()->getParent()->findLayer(layerName);
}

void LayerController::update(Uint32 time)
{
	if (targetLayer == NULL)
		return;

	Uint32 alpha = targetLayer->getOpacity();

	switch (state)
	{
	case FADEIN:
		targetLayer->setOpacity(alpha = (Uint8)min(maxFade, alpha + fadeRate));
		break;
	case FADEOUT:
		targetLayer->setOpacity(alpha = (Uint8)max(minFade, alpha - fadeRate));
		break;
	}

	if ((alpha == maxFade) || (alpha == minFade))
		state = SHOWN;
}

void LayerController::setProperty(string key, string val)
{
	if (key == "minFade")
		minFade = atoi(val.c_str());
	else if (key == "maxFade")
		maxFade = atoi(val.c_str());
	else if (key == "fadeRate")
		fadeRate = atoi(val.c_str());
	else if (key == "layer")
		layerName = val;
	else
		WorldObject::setProperty(key, val);
}

WorldInput LayerController::resolveInput(string inpName)
{
	if (inpName == "hide")
		return GET_INPUT_POINTER(&LayerController::hide);
	else if (inpName == "show")
		return GET_INPUT_POINTER(&LayerController::show);
	else if (inpName == "fadeOut")
		return GET_INPUT_POINTER(&LayerController::fadeOut);
	else if (inpName == "fadeIn")
		return GET_INPUT_POINTER(&LayerController::fadeIn);
	else
		return WorldObject::resolveInput(inpName);
}
