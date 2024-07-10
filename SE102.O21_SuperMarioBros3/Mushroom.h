#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_MUSHROOM 90000

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_WALKING_SPEED 0.06f

#define MUSHROOM_WIDTH 16
#define MUSHROOM_BBOX_WIDTH 14
#define MUSHROOM_BBOX_HEIGHT 16

#define MUSHROOM_STATE_WALKING 100
#define MUSHROOM_STATE_VISIBILITY 200
#define MUSHROOM_STATE_DIE 300


#define MUSROOM_TIMEOUT_VISIBILITY 1600

class CMushroom : public CGameObject {
protected:
	float ax;
	float ay;
	int typeMushroom;

	ULONGLONG walk_start;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
public:
	CMushroom(float x, float y, int type);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void SetState(int state);
	void OnCollisionWithMario(float mx, float my);
	int GetTypeMushroom() { return typeMushroom; }
};