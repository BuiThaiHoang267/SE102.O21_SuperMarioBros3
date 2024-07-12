#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CPanelUI : public CGameObject {
protected:
	int width;
	int height;
	int spriteId;
	float posX;
	float posY;
public:
	CPanelUI(float x, float y, int widthh, int heightt, int sipriteIdd) : CGameObject(x, y)
	{
		this->width = widthh;
		this->height = heightt;
		this->spriteId = sipriteIdd;
		posX = posY = 0;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
};