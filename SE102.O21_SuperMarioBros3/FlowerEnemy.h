#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define FLOWERENEMY_STATE_IDLE 1
#define FLOWERENEMY_STATE_UP 2
#define FLOWERENEMY_STATE_FIRE 3
#define FLOWERENEMY_STATE_DOWN 4

#define ID_NOTANI_FLOWERENEMY_LEFT_LOW 310000
#define ID_NOTANI_FLOWERENEMY_LEFT_HIGH 312000
#define ID_NOTANI_FLOWERENEMY_RIGHT_LOW 314000
#define ID_NOTANI_FLOWERENEMY_RIGHT_HIGH 316000

#define ID_ANI_FLOWERENEMY_UPDOWN_LEFT_LOW 310000
#define ID_ANI_FLOWERENEMY_UPDOWN_LEFT_HIGH 312000

#define ID_ANI_FLOWERENEMY_UPDOWN_RIGHT_LOW 314000
#define ID_ANI_FLOWERENEMY_UPDOWN_RIGHT_HIGH 316000

#define FLOWERENEMY_VY_UP -0.05f

#define FLOWERENEMY_BBOX_WIDTH 16
#define FLOWERENEMY_BBOX_HEIGHT 32

class CFlowerEnemy : public CGameObject {
private:
	int distanceY = 32;
	int posY;
	ULONGLONG fire_start;
	bool isLeft;
	bool isHigh;
	int aniId;
public:
	CFlowerEnemy(float x, float y) : CGameObject(x, y) {
		this->state = FLOWERENEMY_STATE_UP;
		this->posY = y;
		vy = FLOWERENEMY_VY_UP;
		this->fire_start = -1;
		this->isLeft = true;
		this->isHigh = true;
		this->aniId = ID_NOTANI_FLOWERENEMY_LEFT_LOW;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	int IsBlocking() { return 1; }
	int GetIdAni();
};