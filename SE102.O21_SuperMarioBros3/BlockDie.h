#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CBlockDie : public CGameObject {
protected:
	int width;
	int height;
	float posX;
	float posY;
public:
	CBlockDie(float x, float y, int widthh, int heightt) : CGameObject(x, y)
	{
		this->width = widthh;
		this->height = heightt;
		posX = x;
		posY = y;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 1; }
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnTriggerStay(LPCOLLISIONEVENT e);
};