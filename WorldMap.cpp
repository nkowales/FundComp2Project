/*
 * WorldMap.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: naiello
 */

#include "WorldMap.h"
#include "TileLayer.h"
#include <cstdlib>
#include <sstream>

using namespace std;
using namespace rapidxml;

WorldMap::WorldMap()
{
	width = height = tileSize = 0;
}

WorldMap::WorldMap(string fname, ContentManager& content) : WorldMap()
{
	load(fname, content);
}

WorldMap::~WorldMap()
{
	// Free memory for all map layers
	for (vector<MapLayer*>::iterator iter = layers.begin(); iter != layers.end(); iter++)
	{
		delete *iter;
	}

	layers.clear();
}

void WorldMap::draw(SDL_Renderer* renderer)
{
	// Draw each map layer
	for (vector<MapLayer*>::iterator iter = layers.begin(); iter != layers.end(); iter++)
	{
		(*iter)->draw(renderer);
	}
}

void WorldMap::load(string fname, ContentManager& content)
{
	file<> fl(fname.c_str());
	xml_document<> doc;

	//cout << fl.data() << endl;

	// Load the file data into the parser
	doc.parse<0>(fl.data());

	// Get a pointer to the root <map> node
	xml_node<>* root = doc.first_node("map");
	xml_attribute<>* attr;

	// Parse basic map info
	width = atoi(root->first_attribute("width")->value());
	height = atoi(root->first_attribute("height")->value());
	tileSize = atoi(root->first_attribute("tilewidth")->value());

	// Parse list of tilesets
	for (xml_node<>* tsetNode = root->first_node("tileset"); tsetNode; tsetNode = tsetNode->next_sibling("tileset"))
	{
		string tsetFile;
		Uint32 fgid = 0, tspc = 0, border = 0, tsz = 1;

		attr = tsetNode->first_attribute("firstgid");
		if (attr)
			fgid = atoi(attr->value());

		attr = tsetNode->first_attribute("spacing");
		if (attr)
			tspc = atoi(attr->value());

		attr = tsetNode->first_attribute("tilewidth");
		if (attr)
			tsz = atoi(attr->value());

		attr = tsetNode->first_attribute("margin");
		if (attr)
			border = atoi(attr->value());

		tsetFile = tsetNode->first_node("image")->first_attribute("source")->value();

		// Load the texture thru the Content Manager
		Texture& tiletex = content.getTexture(tsetFile);

		// Read image dimensions
		int imgw, imgh;
		tiletex.getDimensions(&imgw, &imgh);

		// Convert from pixels to tiles
		imgw = (imgw - border * 2) / (tsz + tspc);
		imgh = (imgh - border * 2) / (tsz + tspc);

		// Add the tileset to the list
		Tileset tset(tiletex.getImage(), tsz, tspc, border, imgw, imgh, fgid);
		tilesets.push_back(tset);
	}

	// Read in each tile layer
	for (xml_node<>* tileLayer = root->first_node("layer"); tileLayer; tileLayer = tileLayer->next_sibling("layer"))
	{
		bool vis = true;
		Uint8 opacity = 255;

		// Is this layer visible by default?
		attr = tileLayer->first_attribute("visible");
		if (attr)
			vis = atoi(attr->value());

		// How transparent is this layer?
		attr = tileLayer->first_attribute("opacity");
		if (attr)
			opacity = atof(attr->value()) * 255.;

		xml_node<>* dataNode = tileLayer->first_node("data");

		// Read in tile data
		vector<Uint32> tlist;
		stringstream data(dataNode->value());

		Uint32 tile;
		while (data >> tile)
		{
			tlist.push_back(tile);

			if ((data.peek() == ',') || (data.peek() == ' ') || (data.peek() == '\n'))
				data.ignore();
		}

		TileLayer* tlayer = new TileLayer(this, tlist);
		tlayer->setVisible(vis);
		tlayer->setOpacity(opacity);
		layers.push_back(tlayer);
	}
}

void WorldMap::getDimensions(Uint32* w, Uint32* h) const
{
	if (w)
		*w = width;

	if (h)
		*h = height;
}

Uint32 WorldMap::getTileSize() const
{
	return tileSize;
}

const Tileset* WorldMap::resolveTile(Uint32 gid) const
{
	/*vector<Tileset>::const_iterator iter = tilesets.begin();
	for (vector<Tileset>::const_iterator iter2 = tilesets.begin() + 1; iter != tilesets.end(); iter++, iter2++)
	{
		// If the tile GID is found within this tileset, return a pointer to it
		if ((iter->getFirstGid() <= gid) && (((iter2 == tilesets.end()) && (iter->getFirstGid() + iter->getTileCount() < gid)) ||
				((iter2 != tilesets.end()) && (iter2->getFirstGid() < gid))))
		{
			return &(*iter);
		}
	}*/

	Uint32 i;
	bool hitEnd = true;
	for (i = 0; i < tilesets.size(); i++)
	{
		if (tilesets[i].getFirstGid() > gid)
		{
			i--;
			hitEnd = false;
			break;
		}
	}

	if (hitEnd)
		i--;

	return &tilesets[i];
}
