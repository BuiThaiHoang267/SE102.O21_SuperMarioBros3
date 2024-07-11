#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "CheckMove.h"

#define ID_ANI_TURTLE_TORTOISESHELL 430000

#define ID_ANI_TURTLE_WALK_LEFT 400000
#define ID_ANI_TURTLE_WALK_RIGHT 400001

#define ID_ANI_TURTLE_RUN_LEFT 410000
#define ID_ANI_TURTLE_RUN_RIGHT 410001

#define ID_ANI_TURTLE_WAKEUP 420000

#define ID_ANI_TURTLE_JUMP_LEFT 440001
#define ID_ANI_TURTLE_JUMP_RIGHT 440002

#define ID_ANI_TURTLE_DIE 450001

#define TURTLE_BBOX_WIDTH 14
#define TURTLE_BBOX_HEIGHT 16

#define TURTLE_STATE_JUMP 0
#define TURTLE_STATE_WALK 1
#define TURTLE_STATE_TORTOISESHELL 2
#define TURTLE_STATE_RUN 3
#define TURTLE_STATE_WAKEUP 4
#define TURTLE_STATE_MARIO_HOLD 5
#define TURTLE_STATE_DIE 6

#define TURTLE_VX_STATE_WALK 0.024f
#define TURTLE_VX_STATE_RUN 0.24f
#define TURTLE_VY_JUMP -0.28f
#define TURTLE_VY_MAX_FALL 0.18f
#define TURTLE_VY_DIE -0.3f
#define TURTLE_VX_DIE 0.1f

#define TURTLE_GRAVITY 0.001f

#define TURTLE_RETURN_TIMEOUT 5000
#define TURTLE_WAKEUP_TIMEOUT 2500

#define OFFSET_CHECKMOVE_X 4
#define OFFSET_CHECKMOVE_Y 10

#define TURTLE_TYPE_RED 0
#define TURTLE_TYPE_GREEN 1
#define TURTLE_TYPE_GREEN_WING 2

class CTurtle : public CGameObject {
private:
	float ay;
	int aniId;
	int offsetYBBox;
	ULONGLONG tortoiseshell_start;
	ULONGLONG wakeup_start;
	CCheckMove* checkmove;
	int type;
	bool isStatic;
	bool isOnPlatform;
	int flexDirection;
	int isBlock;
public:
	CTurtle(float x, float y, int direction, int typeTurte) : CGameObject(x, y) 
	{
		this->tag = TAG_ENEMY;
		this->tortoiseshell_start = -1;
		this->ay = TURTLE_GRAVITY;
		this->aniId = ID_ANI_TURTLE_WALK_LEFT;
		this->offsetYBBox = 0;
		this->wakeup_start = 0;
		this->checkmove = new CCheckMove(x - OFFSET_CHECKMOVE_X, y + OFFSET_CHECKMOVE_Y,  4,  4);
		this->isStatic = false;
		this->flexDirection = direction;
		this->type = typeTurte;
		this->isBlock = 1;
		this->isOnPlatform = false;
		if (type == 2) 
		{
			SetState(TURTLE_STATE_JUMP);
		}
		else
		{
			SetState(TURTLE_STATE_WALK);
		}
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return isBlock; };
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void SetState(int state);
	int GetAniId();
	void UpdatePosCheckMove();
	void SetDirectionRun(int direction);
	void OnCollisionWhenStateRun(LPCOLLISIONEVENT e);
	void Die(int direction);
};