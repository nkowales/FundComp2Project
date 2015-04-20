/*
 * Boomerang.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: naiello
 */

#include "Boomerang.h"
#include "ObjectLayer.h"

Boomerang::Boomerang(Uint32 id) : WorldObject(id)
{
	setCollisionGroup(COLGRP_PROJECTILE);
	setBoundingBox({0, 0, BOOMERANG_SIZE, BOOMERANG_SIZE});
}

void Boomerang::init(ContentManager* content)
{
	sprite = content->getAnimatedTexture("sprites/Link.png", 36, 543, 10, 10, 2, 4, 5);
	position = bezierCurve[0];
}

void Boomerang::update(Uint32 time)
{
	// Wait for player's animation to finish
	if (delay > 0)
	{
		delay--;
		return;
	}

	Vector2d target;
	if (currentTarget != -1)
	{
		target = bezierCurve[currentTarget];
	}
	else if (returnTo)
	{
		target = returnTo->getPosition();
	}

	if (distanceSquare(target, position) < BOOMERANG_SIZE / 2)
	{
		if (currentTarget == -1)
			getParentLayer()->removeObject(getId());
		else if (++currentTarget == bezierCurve.size())
			currentTarget = -1;
	}

	double dx = target.x - position.x;
	double dy = target.y - position.y;
	double dist = sqrt(dx * dx + dy * dy);

	if (dist == 0.0)
		return;

	velocity.x = BOOMERANG_SPEED * (dx / dist);
	velocity.y = BOOMERANG_SPEED * (dy / dist);


	WorldObject::update(time);
}

// Adapted from http://devmag.org.za/2011/04/05/bzier-curves-a-tutorial/
Vector2d Boomerang::calculateBezierPoint(double t, Vector2d p1, Vector2d p2, Vector2d p3, Vector2d p4)
{
	double u = 1. - t;		// u = complement of t
	double t2 = t * t;		// t2 = t squared
	double u2 = u * u;		// u2 = u squared
	double t3 = t2 * t;		// t3 = t cubed
	double u3 = u2 * u;		// u3 = u cubed

	Vector2d result = u3 * p1 + 3 * u2 * t * p2 + 3 * u * t2 * p3 + t3 * p4;
	//cout << result.x << ", " << result.y << endl;
	return result;
}

// Adapted from http://devmag.org.za/2011/04/05/bzier-curves-a-tutorial/
void Boomerang::setPath(const Path& ctrlPts)
{
	for (Uint32 i = 0; i < ctrlPts.size() - 3; i += 3)
	{
		Vector2d p1 = ctrlPts[i];
		Vector2d p2 = ctrlPts[i + 1];
		Vector2d p3 = ctrlPts[i + 2];
		Vector2d p4 = ctrlPts[i + 3];

		if (i == 0)
			bezierCurve.push_back(calculateBezierPoint(0, p1, p2, p3, p4));

		for (int j = 0; j <= SEGMENTS_PER_CURVE; j++)
		{
			double t = j / (double)SEGMENTS_PER_CURVE;
			bezierCurve.push_back(calculateBezierPoint(t, p1, p2, p3, p4));
		}
	}
}

void Boomerang::setReturnTarget(WorldObject* obj)
{
	returnTo = obj;
}

void Boomerang::draw(SDL_Renderer* renderer)
{
	// Draw path
	/*SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	Camera* cam = getCamera();
	Vector2d first = cam->transform(bezierCurve[0]);
	Vector2d second;
	for (Uint32 i = 1; i < bezierCurve.size(); i++)
	{
		second = cam->transform(bezierCurve[i]);
		SDL_RenderDrawLine(renderer, first.x, first.y, second.x, second.y);
		first = second;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);*/

	if (delay == 0)
	{
		Vector2d pos = getCamera()->transform(position);
		sprite.draw(renderer, pos.x, pos.y);
	}
}

bool Boomerang::isReturning()
{
	return (currentTarget == -1);
}