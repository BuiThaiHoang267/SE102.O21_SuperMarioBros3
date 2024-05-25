#pragma once

#include "Animation.h"
#include "Animations.h"
#include "Effect.h"

#define ID_ANI_COINBOX 100000

#define EF_COINBOX_WIDTH 8
#define EF_COINBOX_HEIGHT 16

#define COINBOX_VY_START -0.5f
#define COINBOX_GRAVITY 0.002f


class CEffectCoinBox : public CEffect {
private:
	float posY;
public:
	CEffectCoinBox(float x, float y) : CEffect(x, y) {
		this->posY = y;
		this->vy = COINBOX_VY_START;
	};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};