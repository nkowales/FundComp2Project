/*
 * HammerBro.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: naiello
 */

#include "HammerBro.h"
#include "ObjectLayer.h"
#include "Hammer.h"
HammerBro::HammerBro(Uint32 id) : Enemy(id)
{

}

void HammerBro::init(ContentManager* content)
{
	setName("HammerBro");
	setBoundingBox({0, 0, HAMMERBRO_WIDTH, HAMMERBRO_HEIGHT});
	setMaxHealth(HAMMERBRO_HEALTH);
	setHealth(HAMMERBRO_HEALTH);
	setContactDamage(15);		// Damage taken by player for walking into the HammerBro

	sprite = content->getAnimatedTexture("sprites/M-hammerkoopa.png", 16, 14, 18, 28, 0, 3, 20);
	velocity.x = 0;
}

void HammerBro::onWalkIntoWall(WorldObject* wall, const SDL_Rect& overlap)
{
	
}

void HammerBro::draw(SDL_Renderer* renderer)
{
	SDL_Rect bbox = getCamera()->transform(getBoundingBox());
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &bbox);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	Vector2d tpos = getCamera()->transform(position);
	sprite.draw(renderer, tpos.x, tpos.y);
}
void HammerBro::throwHammer(){
	Hammer* ham;
	Vector2d fpos;
	if (hammerCooldown > 0.){}
	else
	{
		hammerCooldown = HAMMER_COOLDOWN;
		ham = new Hammer(WorldObject::getUniqueID());
		fpos = {(facingLeft) ? position.x : position.x + HAMMERBRO_WIDTH, position.y + HAMMERBRO_HEIGHT};
		ham->setPosition(fpos);
		if (facingLeft)
			ham->reverseDirection();
		getParentLayer()->addObject(ham);
	}


}
void HammerBro::squish(){
	die();
}
