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
#define SPYRO_JUMP_VEL 340
#define PLAYER_JUMP_TOL 5
#define PLAYER_FLYING_FRAMETOL 1
#define PLAYER_HEAD_ELASTICITY 0.5
#define PLAYER_FEET 40
#define MARIO_WIDTH 16
#define MARIO_HEIGHT 27
#define SPYRO_HEIGHT 40
#define SPYRO_WIDTH 49
#define SPYRO_JUMP_ANIMSPD 4
#define SPYRO_ANIMSPD 4
#define LBLUERUN_WIDTH 55
#define LBLUERUN_HEIGHT 35
#define LBLUE_WIDTH 49
#define LBLUE_HEIGHT 35
#define LINK_WIDTH 20
#define LINK_HEIGHT 24

#define GRAVITY 600
#define SPYRO_GRAVITY 100

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
	CH_MCHIEF,
	CH_LBLUE
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
	bool inAir = false;
	bool canJump = true;
	bool standingOnOneWay = false;
	OneWayPlatform* lastOneWay = NULL;
	OneWayPlatform* ignorePlatform = NULL;
	Uint32 framesSinceTouchedGround = 0;

	//AnimatedTexture marioSprite;
	//AnimatedTexture spyroSprite;
	//AnimatedTexture lBlueSprite;
	//AnimatedTexture linkSprite;
	vector<AnimatedTexture> sprites;
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
	void switchCharacter(int character);
	void glide();
};


#endif /* PLAYER_H_ */
