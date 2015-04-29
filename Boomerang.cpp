/*
 * Boomerang.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: naiello
 */

#include "Boomerang.h"
#include "ObjectLayer.h"

Boomerang::Boomerang(Uint32 id) : Projectile(id)
{
	velocity.x = 250;
	velocity.y = 200;
	maxBounces = 3;
	size = 10;
	gravity = 800;
	damage = 5;
	setCollisionGroup(COLGRP_PROJECTILE);
	setBoundingBox({0, 0, BOOMERANG_SIZE, BOOMERANG_SIZE});
	
}

void Boomerang::init(ContentManager* content)
{

	sprite = content->getAnimatedTexture("sprites/L-Link.png", 36, 543, 10, 10, 2, 4, 5);
	position = bezierCurve[0];
	sound = content->getSfx("Music/LOZ_Boomerang.wav");
	
}

void Boomerang::update(Uint32 time)
{
	double secs = time / 1000.;
	// Wait for player's animation to finish
	soundDelay -= secs;
	if (delay > 0)
	{
		delay--;
		return;
	}

	if (soundDelay < 0.)
	{
		//cout << soundDelay << " now playing sound" << endl;
		Mix_PlayChannel(-1, sound, 0);
		soundDelay = 0.2;	
	}
	Vector2d target;
	if (currentTarget != -1)
	{
		
		target = bezierCurve[currentTarget];
	}
	else if (returnTo)
	{
		//Mix_PlayChannel(-1, sound, 0);
		target = returnTo->getPosition();
	}

	if (distanceSquare(target, position) < (BOOMERANG_SIZE * BOOMERANG_SIZE))
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
	// Generate a smooth path from the control points given
	for (Uint32 i = 0; i < ctrlPts.size() - 3; i += 3)
	{
		Vector2d p1 = ctrlPts[i];
		Vector2d p2 = ctrlPts[i + 1];
		Vector2d p3 = ctrlPts[i + 2];
		Vector2d p4 = ctrlPts[i + 3];

		if (i == 0)
			bezierCurve.push_back(calculateBezierPoint(0, p1, p2, p3, p4));

		// Interpolate between control points at set intervals
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
bool Boomerang::canCollideWith(const WorldObject* other)
{
	Uint32 grp = other->getCollisionGroup();
	return ( (grp == COLGRP_ENEMY) );
}
void Boomerang::handleCollision(WorldObject* other, const SDL_Rect& overlap)
{
	Uint32 grp = other->getCollisionGroup();
	Enemy* enemy;
	switch (grp)
	{
	case COLGRP_ENEMY:
		enemy = static_cast<Enemy*>(other);
		if (enemy->getInvuln() == true){
		} else{
			enemy->stun();
			currentTarget = -1;
		}
		break;
	default:
		break;
	}

	
}
