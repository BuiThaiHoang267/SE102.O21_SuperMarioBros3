#pragma once
#include "GameObject.h"

#define GOOMBAJUMP_GRAVITY 0.001f
#define GOOMBAJUMP_WALKING_SPEED 0.03f
#define GOOMBAJUMP_VY_JUMP 0.08f
#define GOOMBAJUMP_VY_JUMP_MAX 0.30f


#define GOOMBAJUMP_BBOX_WIDTH 16
#define GOOMBAJUMP_BBOX_HEIGHT 14
#define GOOMBAJUMP_BBOX_HEIGHT_DIE 7

#define GOOMBAJUMP_DIE_TIMEOUT 500
#define GOOMBAJUMP_DIE_TORTOISESHELL_TIMEOUT 2000

#define GOOMBAJUMP_STATE_JUMP 100
#define GOOMBAJUMP_STATE_WALKING 200
#define GOOMBAJUMP_STATE_DIE 300
#define GOOMBAJUMP_STATE_DIE_TORTOISESHELL 400

#define GOOMBAJUMP_LEVEL_WING 2
#define GOOMBAJUMP_LEVEL_NORMAL 1

#define ID_ANI_GOOMBAJUMP_JUMPING 35001
#define ID_ANI_GOOMBAJUMP_WALKING_WING 35000
#define ID_ANI_GOOMBAJUMP_WALKING 33000
#define ID_ANI_GOOMBAJUMP_DIE 34000
#define ID_ANI_GOOMBAJUMP_DIE_TORTOISESHELL 34001

class CGoombaJump : public CGameObject
{
protected:
	float ax;
	float ay;
	bool isOnPlatform;
	int aniId;
	int level;
	int countJump;

	ULONGLONG die_start;
	ULONGLONG walk_start;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return (state != GOOMBAJUMP_STATE_DIE_TORTOISESHELL); }
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);
	int GetAniId();
public:
	CGoombaJump(float x, float y) : CGameObject(x, y) 
	{
		this->tag = TAG_ENEMY;
		this->ax = 0;
		this->ay = GOOMBAJUMP_GRAVITY;
		this->die_start = -1;
		this->aniId = ID_ANI_GOOMBAJUMP_WALKING_WING;
		this->isOnPlatform = true;
		this->level = GOOMBAJUMP_LEVEL_WING;
		this->countJump = 0;
		this->vx = -GOOMBAJUMP_WALKING_SPEED;
		SetState(GOOMBAJUMP_STATE_WALKING);
	};
	void SetState(int state);
	void SetLevel(int level);
	int GetLevel();
	void DieFromTortoiseshell(int flexDirection);
};