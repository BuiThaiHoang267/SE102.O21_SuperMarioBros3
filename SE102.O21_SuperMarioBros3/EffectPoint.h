#pragma once

#include "Animation.h"
#include "Animations.h"
#include "Effect.h"

#define ID_ANI_POINT_100 110000
#define ID_ANI_POINT_1000 111000

#define EF_POINT_WIDTH 12
#define EF_POINT_HEIGHT 8

#define POINT_VY_START -0.06f
#define POINT_GRAVITY_START 0.00005f


class CEffectPoint : public CEffect {
private:
	int point;
	float ay;
public:
	CEffectPoint(float x, float y, int pointt) : CEffect(x, y) {
		this->point = pointt;
		this->vy = POINT_VY_START;
		this->ay = POINT_GRAVITY_START;
	};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};