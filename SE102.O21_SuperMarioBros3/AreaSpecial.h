#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Mario.h"

class CAreaSpecial : public CGameObject {
protected:
	int height;
	int width;
	float posX;
	float posY;
public:
	CAreaSpecial(float x, float y, int widthh, int heightt) : CGameObject(x, y)
	{
		this->width = widthh;
		this->height = heightt;
		posX = x;
		posY = y;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }
};
