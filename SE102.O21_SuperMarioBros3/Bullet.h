#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BULLET 40000

#define BULLET_BBOX_WIDTH 6
#define BULLET_BBOX_HEIGHT 6

class CBullet : public CGameObject {

public:
	CBullet(float x, float y, float posX, float posY) : CGameObject(x, y) 
	{
		SetUpAngle(posX, posY);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; };
	void SetUpAngle(float posX,float posY);
};