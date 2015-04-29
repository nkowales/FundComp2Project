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
#include "ProgressBar.h"

using namespace std;

#define PLAYER_WALK_SPEED 150
#define PLAYER_SHUFFLE_SPEED 50
#define PLAYER_JUMP_VEL 275
#define SPYRO_JUMP_VEL 340
#define PLAYER_JUMP_TOL 5
#define PLAYER_FLYING_FRAMETOL 1
#define PLAYER_HEAD_ELASTICITY 0.5
#define PLAYER_FEET 40
#define MARIO_WIDTH 16
#define MARIO_HEIGHT 27
#define SPYRO_HEIGHT 30
#define SPYRO_WIDTH 38
#define SPYRO_JUMP_ANIMSPD 4
#define SPYRO_ANIMSPD 4
#define LBLUERUN_WIDTH 55
#define LBLUERUN_HEIGHT 35
#define LBLUE_WIDTH 49
#define LBLUE_HEIGHT 35
#define LINK_WIDTH 20
#define LINK_HEIGHT 24

#define FIREBALL_COOLDOWN 0.5
#define PLAYER_MAXHEALTH 100
#define PLAYER_INVULN_TIME 1.0

#define HEALTHBAR_W 100
#define HEALTHBAR_H 16
#define HEALTHBAR_OFFSET 10

#define SWORD_DAMAGE 1

#define GRAVITY 600
#define SPYRO_GRAVITY 20

enum PlayerState
{
	PLYR_STANDING,
	PLYR_MVG_RIGHT,
	PLYR_MVG_LEFT,
	PLYR_HOVERING,
	PLYR_FLYING_LEFT,
	PLYR_FLYING_RIGHT,
	PLYR_FLYING_UP,
	PLYR_FLYING_DOWN
};

enum Character
{
	CH_MARIO,
	CH_LINK,
	CH_SPYRO,
	CH_MCHIEF,
	CH_LBLUE
};

enum Level
{
	LVL_MARIO,
	LVL_LINK,
	LVL_SPYRO,
	LVL_BOWSER
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
	bool defending = false;
	bool inAir = false;
	bool canJump = true;
	bool flying = false;
	bool standingOnOneWay = false;
	OneWayPlatform* lastOneWay = NULL;
	OneWayPlatform* ignorePlatform = NULL;
	Uint32 framesSinceTouchedGround = 0;
	vector<AnimatedTexture> sprites;
	bool facingLeft = false;
	int currentCharacter = CH_MARIO;
	bool hasBoomerang = true;
	double fireballCooldown = 0.;
	int health = PLAYER_MAXHEALTH;
	int maxHealth = PLAYER_MAXHEALTH;
	double invulnTimer = 0.;
	int currentLevel = LVL_MARIO; // level 1

	ProgressBar healthBar;

	void moveLeft();
	void moveRight();
	void duck();
	void stopMoveRight();
	void stopMoveLeft();
	void jump();
	void meleeAttack();
	void rangedAttack();
	void resetAnimation();
	void switchCharacter(int);
	void glide();
	void hurt(int);
	void die();
	void resetBBox();
	void switchMode();
	void defend();
};


#endif /* PLAYER_H_ */
