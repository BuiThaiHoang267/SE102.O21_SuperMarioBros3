#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_LEAF_LEFT 91001
#define ID_ANI_LEAF_RIGHT 91002

#define LEAF_BBOX_WIDTH 10
#define LEAF_BBOX_HEIGHT 10

#define LEAF_GRAVITY -0.0001f
#define LEAF_VX 0.1f
#define LEAF_VY 0.05f

class CLeaf : public CGameObject {
protected:
	float ax;
	float ay;
	int flexDirection;
public:
	CLeaf(float x, float y) : CGameObject(x, y) {
		this->ax = 0;
		this->ay = LEAF_GRAVITY;
		this->flexDirection = 1;
		this->vx = LEAF_VX;
		this->vy = LEAF_VY;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};
