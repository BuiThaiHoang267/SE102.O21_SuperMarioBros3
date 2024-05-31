#pragma once
#include "GameObject.h"

#define GOOMBAJUMP_GRAVITY 0.002f
#define GOOMBAJUMP_WALKING_SPEED 0.05f


#define GOOMBAJUMP_BBOX_WIDTH 16
#define GOOMBAJUMP_BBOX_HEIGHT 14
#define GOOMBAJUMP_BBOX_HEIGHT_DIE 7

#define GOOMBAJUMP_DIE_TIMEOUT 500

#define GOOMBAJUMP_STATE_JUMP 100
#define GOOMBAJUMP_STATE_WALKING 200
#define GOOMBAJUMP_STATE_DIE 300

#define ID_ANI_GOOMBAJUMP_JUMP 
#define ID_ANI_GOOMBAJUMP_WALKING 5000
#define ID_ANI_GOOMBAJUMP_DIE 5001

class CGoombaJump : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CGoombaJump(float x, float y) : CGameObject(x, y) 
	{
		this->ax = 0;
		this->ay = GOOMBAJUMP_GRAVITY;
		this->die_start = -1;
	};
	void SetState(int state);
};