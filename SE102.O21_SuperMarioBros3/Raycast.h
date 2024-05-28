#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CRaycast : public CGameObject {
protected:
	int height;
	int width;
	bool isDetectedMario;
	bool isLeft;
	bool isHigh;
public:
	CRaycast(float x, float y, int widthh, int heightt) : CGameObject(x, y)
	{
		this->width = widthh;
		this->height = heightt;
		this->isDetectedMario = false;
		this->isLeft = true;
		this->isHigh = true;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithMario(LPCOLLISIONEVENT e);
	bool GetIsLeft() { return this->isLeft; }
	bool GetIsHigh() { return this->isHigh; }
	bool GetIsDetectedMario() { return this->isDetectedMario; }
};