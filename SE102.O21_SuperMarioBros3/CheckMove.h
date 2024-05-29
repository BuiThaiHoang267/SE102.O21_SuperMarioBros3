#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CCheckMove : public CGameObject {
protected:
	int height;
	int width;
	float ay;
public:
	bool isOnPlatform;
	CCheckMove(float x, float y, int widthh, int heightt) : CGameObject(x, y)
	{
		this->width = widthh;
		this->height = heightt;
		this->isOnPlatform = true;
		this->ay = 0.002f;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	//void OnTriggerEnter(LPCOLLISIONEVENT e);
	//void OnTriggerStay(LPCOLLISIONEVENT e);
	//void OnTriggerExit(LPGAMEOBJECT e);
};
