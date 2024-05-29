#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CBoxColor : public CGameObject {
protected:
	int width;
	int height;
	int spriteId;
	int paddingRight;
public:
	CBoxColor(float x, float y,int widthh, int heightt, int sipriteIdd, int paddingRightt) : CGameObject(x, y) 
	{
		this->width = widthh;
		this->height = heightt;
		this->spriteId = sipriteIdd;
		this->paddingRight = paddingRightt;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsDirectionColliable(float nx, float ny);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 1; }
};