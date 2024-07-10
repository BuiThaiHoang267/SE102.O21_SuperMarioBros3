#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define ID_ANI_BRICK_OPENED 84000

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_IDLE 100
#define BRICK_STATE_OPENED 200
#define BRICK_STATE_BEFORE_OPENED 300

#define BRICK_TYPE_SPECIAL 1
#define BRICK_TYPE_NORMAL 0

#define BRICK_GRAVITY 0.002f

class CBrick : public CGameObject {
	float posX;
	float posY;
	int typeBrick;
	bool canOpen;
public:
	CBrick(float x, float y, int type) : CGameObject(x, y) {
		SetState(BRICK_STATE_IDLE);
		this->posX = x;
		this->posY = y;
		this->typeBrick = type;
		canOpen = false;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	void Break();
	void OpenCoin();
	void OpenMushroom();
	void CanOpen(int levelMario);
};