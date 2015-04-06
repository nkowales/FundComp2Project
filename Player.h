/*
 * Player.h
 *
 *  Created on: Mar 28, 2015
 *      Author: naiello
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include "WorldObject.h"
#include "OneWayPlatform.h"

using namespace std;

#define PLAYER_WALK_SPEED 100
#define PLAYER_JUMP_VEL 275
#define PLAYER_JUMP_TOL 5
#define PLAYER_FLYING_FRAMETOL 1
#define PLAYER_HEAD_ELASTICITY 0.5
#define PLAYER_FEET 6
#define PLAYER_WIDTH 24
#define PLAYER_HEIGHT 48
#define GRAVITY 600

enum PlayerState
{
	PLYR_STANDING,
	PLYR_MVG_RIGHT,
	PLYR_MVG_LEFT
};

class Player : public WorldObject
{
public:
	Player();

	void init();
	void update(Uint32);
	void draw(SDL_Renderer*);
	void handleEvent(const SDL_Event&);
	bool canCollideWith(const WorldObject*);
	void handleCollision(WorldObject*, const SDL_Rect&);

private:
	int state;
	bool inAir;
	bool canJump;
	bool standingOnOneWay;
	OneWayPlatform* lastOneWay = NULL;
	OneWayPlatform* ignorePlatform = NULL;
	Uint32 framesSinceTouchedGround;

	void jump();
};


#endif /* PLAYER_H_ */
