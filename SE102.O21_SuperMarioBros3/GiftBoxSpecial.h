#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define GIFTBOX_WIDTH 16
#define GIFTBOX_BBOX_WIDTH 16
#define GIFTBOX_BBOX_HEIGHT 16

#define ID_ANI_MUSHROOM 90000
#define ID_ANI_STAR 92000
#define ID_ANI_FLOWERBLUE 92001

#define GIFTBOX_SPECIAL_STATE_MUSHROOM 0
#define GIFTBOX_SPECIAL_STATE_STAR 1
#define GIFTBOX_SPECIAL_STATE_FLOWERBLUE 2

#define TIMER_ROTATE 100

#define GIFTBOX_GRAVITY 0.002f

class CGiftBoxSpecial : public CGameObject {
protected:
	float posX;
	float posY;
	ULONGLONG timer_rotate;
public:
	CGiftBoxSpecial(float x, float y) : CGameObject(x, y)
	{
		SetState(GIFTBOX_SPECIAL_STATE_MUSHROOM);
		posX = x;
		posY = y;
		timer_rotate = -1;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OpenGiftBox();
	void CanOpen();
	int IsCollidable() { return 1; }
	int GetAniId();
};