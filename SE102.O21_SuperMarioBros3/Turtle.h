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

#define TURTLE_BBOX_WIDTH 16
#define TURTLE_BBOX_HEIGHT 16

#define TURTLE_STATE_WALK 1
#define TURTLE_STATE_TORTOISESHELL 2
#define TURTLE_STATE_RUN 3
#define TURTLE_STATE_WAKEUP 4

#define TURTLE_VX_STATE_WALK 0.03f
#define TURTLE_VX_STATE_RUN 0.2f

#define TURTLE_GRAVITY 0.002f

#define TURTLE_RETURN_TIMEOUT 5000
#define TURTLE_WAKEUP_TIMEOUT 2500

#define OFFSET_CHECKMOVE_X 8
#define OFFSET_CHECKMOVE_Y 10



class CTurtle : public CGameObject {
private:
	float ay;
	int aniId;
	int offsetYBBox;
	ULONGLONG tortoiseshell_start;
	ULONGLONG wakeup_start;
	CCheckMove* checkmove;
	bool isStatic;
public:
	CTurtle(float x, float y) : CGameObject(x, y) 
	{
		this->tag = TAG_ENEMY;
		this->tortoiseshell_start = -1;
		this->ay = TURTLE_GRAVITY;
		this->aniId = ID_ANI_TURTLE_WALK_LEFT;
		this->offsetYBBox = 0;
		this->wakeup_start = 0;
		this->checkmove = new CCheckMove(x - OFFSET_CHECKMOVE_X, y + OFFSET_CHECKMOVE_Y,  4,  4);
		this->isStatic = false;
		SetState(TURTLE_STATE_WALK);
		//SetState(TURTLE_STATE_RUN);
		//SetState(TURTLE_STATE_TORTOISESHELL);
		//SetState(TURTLE_STATE_RUN);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
	int IsCollidable() { return 1; };
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void SetState(int state);
	int GetAniId();
	void UpdatePosCheckMove();
	void SetDirectionRun(int direction);
	int IsStatic();
};