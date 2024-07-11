#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Raycast.h"
#include "PlayScene.h"
#include "CheckActivity.h"


#define FLOWERENEMY_STATE_IDLE 1
#define FLOWERENEMY_STATE_UP 2
#define FLOWERENEMY_STATE_FIRE 3
#define FLOWERENEMY_STATE_DOWN 4
#define FLOWERENEMY_STATE_NOT_FIRE 5

#define ID_NOTANI_FLOWERENEMY_LEFT_LOW 310000
#define ID_NOTANI_FLOWERENEMY_LEFT_HIGH 312000
#define ID_NOTANI_FLOWERENEMY_RIGHT_LOW 314000
#define ID_NOTANI_FLOWERENEMY_RIGHT_HIGH 316000

#define ID_ANI_FLOWERENEMY_UPDOWN_LEFT_LOW 310000
#define ID_ANI_FLOWERENEMY_UPDOWN_LEFT_HIGH 312000

#define ID_ANI_FLOWERENEMY_UPDOWN_RIGHT_LOW 314000
#define ID_ANI_FLOWERENEMY_UPDOWN_RIGHT_HIGH 316000

#define ID_ANI_FLOWERENEMY_NOT_FIER 320000

#define FLOWERENEMY_VY_UP -0.05f

#define FLOWERENEMY_BBOX_WIDTH 12
#define FLOWERENEMY_BBOX_HEIGHT 28

#define FLOWERENEMY_TYPE_NORMAL	0
#define FLOWERENEMY_TYPE_NOT_FIRE 1
#define FLOWERENEMY_TYPE_GREEN 2

class CFlowerEnemy : public CGameObject {
private:
	int distanceY = 32;
	int posY;
	ULONGLONG fire_start;
	bool isLeft;
	bool isHigh;
	bool isFired;
	int aniId;
	int type;
	int offsetYCheckActivity;
	LPGAMEOBJECT shootRange;
	LPGAMEOBJECT checkActivity;
public:
	CFlowerEnemy(float x, float y, int typeFlower) : CGameObject(x, y) {
		this->state = FLOWERENEMY_STATE_UP;
		this->posY = y;
		vy = FLOWERENEMY_VY_UP;
		this->fire_start = -1;
		this->isLeft = true;
		this->isHigh = true;
		this->aniId = ID_NOTANI_FLOWERENEMY_LEFT_LOW;
		this->isFired = false;
		this->type = typeFlower;

		shootRange = new CRaycast(x, y, 232, 300);
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		p->AddGameObject(shootRange);
		
		if (type > 0)
			offsetYCheckActivity = -4;
		else
			offsetYCheckActivity = 8;
		checkActivity = new CCheckActivity(x, y + offsetYCheckActivity, 40, 54);
		p->AddGameObject(checkActivity);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	int IsBlocking() { return 1; }
	int IsCollidable() { return 1; }
	int GetIdAni();
};