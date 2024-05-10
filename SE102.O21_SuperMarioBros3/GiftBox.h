#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define GIFTBOX_WIDTH 16
#define GIFTBOX_BBOX_WIDTH 16
#define GIFTBOX_BBOX_HEIGHT 16

#define ID_ANI_GIFTBOX_IDLE 80000
#define ID_ANI_GIFTBOX_OPENED 84000

#define GIFTBOX_STATE_IDLE 100
#define GIFTBOX_STATE_OPENED 200
#define GIFTBOX_STATE_BEFORE_OPENED 300

#define GIFTBOX_GRAVITY 0.002f

class CGiftBox : public CGameObject {
protected:
	float posX;
	float posY;
	int typeGift;
public:
	CGiftBox(float x, float y, int type) : CGameObject(x, y) 
	{
		SetState(GIFTBOX_STATE_IDLE);
		posX = x;
		posY = y;
		typeGift = type;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OpenGiftBox();
	void CanOpen();
	int IsCollidable() { return 1; }
};