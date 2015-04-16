/*
 * Player.h
 *
 *  Created on: Mar 28, 2015
 *      Author: naiello
 *
 *      This class contains the basic update, draw, and collide logic for the Player class.  The Player CANNOT be directly
 *      inserted into the map from Tiled, and must be spawned by a PlayerSpawn object.
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include "WorldObject.h"
#include "OneWayPlatform.h"

using namespace std;

#define PLAYER_WALK_SPEED 150
#define PLAYER_JUMP_VEL 275
#define PLAYER_JUMP_TOL 5
#define PLAYER_FLYING_FRAMETOL 1
#define PLAYER_HEAD_ELASTICITY 0.5
#define PLAYER_FEET 6
#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 27
#define GRAVITY 600

enum PlayerState
{
	PLYR_STANDING,
	PLYR_MVG_RIGHT,
	PLYR_MVG_LEFT
};

enum Character
{
	CH_MARIO,
	CH_LINK,
	CH_SPYRO,
	CH_MCHIEF
};

class Player : public WorldObject
{
public:
	Player();

	void init(ContentManager* content);
	void update(Uint32);
	void draw(SDL_Renderer*);
	void handleEvent(const SDL_Event&);
	bool canCollideWith(const WorldObject*);
	void handleCollision(WorldObject*, const SDL_Rect&);
	

private:
	int state = PLYR_STANDING;
	int character = CH_MARIO;
	int character2 = CH_SPYRO;
	bool inAir = false;
	bool canJump = true;
	bool standingOnOneWay = false;
	OneWayPlatform* lastOneWay = NULL;
	OneWayPlatform* ignorePlatform = NULL;
	Uint32 framesSinceTouchedGround = 0;

	AnimatedTexture marioSprite;
	AnimatedTexture spyroSprite;
	bool facingLeft = false;
	int currentCharacter = CH_MARIO;
	void moveLeft();
	void moveRight();
	void duck();
	void stopMoveRight();
	void stopMoveLeft();
	void jump();
	void meleeAttack();
	void rangedAttack();
	void resetAnimation();
	void switchCharacter();
};


#endif /* PLAYER_H_ */
