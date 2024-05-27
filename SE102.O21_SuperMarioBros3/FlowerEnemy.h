#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define FLOWERENEMY_STATE_IDLE 1
#define FLOWERENEMY_STATE_UP 2
#define FLOWERENEMY_STATE_FIRE 3
#define FLOWERENEMY_STATE_DOWN 4

#define ID_ANI_FLOWERENEMY 85000
#define ID_NOTANI_FLOWERENEMY 85000

#define	FLOWERENEMY_WIDTH 10
#define FLOWERENEMY_BBOX_WIDTH 10
#define FLOWERENEMY_BBOX_HEIGHT 16

class CFlowerEnemy : public CGameObject {
protected:
	int isAnimation;
public:
	CFlowerEnemy(float x, float y, int isAnim) : CGameObject(x, y) {
		this->isAnimation = isAnim;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	int IsBlocking() { return 1; }
};