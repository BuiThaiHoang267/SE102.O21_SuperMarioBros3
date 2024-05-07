#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CBoxColor : public CGameObject {
protected:
	int width;
	int height;
	int spriteId;
public:
	CBoxColor(float x, float y,int widthh, int heightt, int sipriteIdd) : CGameObject(x, y) 
	{
		this->width = widthh;
		this->height = heightt;
		this->spriteId = sipriteIdd;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsDirectionColliable(float nx, float ny);
};