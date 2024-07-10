#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CBlock : public CGameObject {
protected:
	int width;
	int height;
public:
	CBlock(float x, float y, int widthh, int heightt) : CGameObject(x, y)
	{
		this->width = widthh;
		this->height = heightt;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 1; }
};