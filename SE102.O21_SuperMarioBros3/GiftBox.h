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

class CGiftBox : public CGameObject {
public:
	CGiftBox(float x, float y) : CGameObject(x, y) 
	{
		SetState(GIFTBOX_STATE_IDLE);
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OpenGiftBox();
	int IsCollidable() { return 1; }
};