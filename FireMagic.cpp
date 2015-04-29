/*
 * FireMagic.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: mtroy2
 */

#include "FireMagic.h"
#include "ObjectLayer.h"

FireMagic::FireMagic(Uint32 id) : WorldObject(id)
{
	SDL_Rect bbox = {0, 0, FIREMAGIC_FRMW, FIREMAGIC_FRMH};
	setBoundingBox(bbox);
	setCollisionGroup(COLGRP_ENEMPROJECTILE);

}

void FireMagic::init(ContentManager* content)
{
	sprite = content->getAnimatedTexture("sprites/L-firewizard.png", 147, 25, FIREMAGIC_FRMW,
			FIREMAGIC_FRMH, FIREMAGIC_SPC, FIREMAGIC_NFRM, FIREMAGIC_ANIMSPD);
}

bool FireMagic::canCollideWith(const WorldObject* other)
{
	Uint32 grp = other->getCollisionGroup();
	return ( (grp == COLGRP_WORLD)||(grp == COLGRP_PLAYER) );

}

void FireMagic::update(Uint32 time)
{
	if (delay > 0)
		return;
	double secs = time / 1000.;
	
	WorldObject::update(time);
}


void FireMagic::handleCollision(WorldObject* other, const SDL_Rect& overlap)
{
	kill();
	
}

void FireMagic::draw(SDL_Renderer* renderer)
{
	if (delay > 0 ){
		delay--;
		return;
	}
	SDL_Rect rect = getCamera()->transform(getBoundingBox());
	sprite.draw(renderer, rect.x, rect.y, FIREMAGIC_SCALE, FIREMAGIC_SCALE);
}

void FireMagic::kill()
{
	getParentLayer()->removeObject(getId());
}
void FireMagic::reverseDirection()
{
	velocity.x = -velocity.x;
}
int FireMagic::getContactDamage()
{
	return contactDamage;
}
void FireMagic::setFlipH(bool x){
	sprite.setFlipH(x);
}
