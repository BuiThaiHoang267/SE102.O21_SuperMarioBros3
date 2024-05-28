#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Mario.h"

class CCheckActivity : public CGameObject {
protected:
	int height;
	int width;
	bool isDetectedMario;
public:
	CCheckActivity(float x, float y, int widthh, int heightt) : CGameObject(x, y)
	{
		this->width = widthh;
		this->height = heightt;
		this->isDetectedMario = false;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }
	bool GetIsDetectedMario() { return this->isDetectedMario; }
	void OnTriggerEnter(LPCOLLISIONEVENT e);
	void OnTriggerStay(LPCOLLISIONEVENT e);
	void OnTriggerExit(LPGAMEOBJECT e);
};
