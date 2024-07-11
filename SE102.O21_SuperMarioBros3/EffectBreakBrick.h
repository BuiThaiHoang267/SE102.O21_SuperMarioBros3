#pragma once
#include <cmath>
#include "Effect.h"

#define EF_BREAKBRICK_WIDTH 8
#define EF_BREAKBRICK_HEIGHT 8

#define ID_ANI_BREAK_BRICK 112000

#define TIMER_DIE_BREAKBRICK 3000

#define BREAKBRICK_GRAVITY 0.001f

class CEffectBreakBrick : public CEffect {
private:
	float ay;
	float ax;
	ULONGLONG timer_die;
public:
	CEffectBreakBrick(float x, float y, float speed, float angleInit) : CEffect(x, y)
	{
		ax = 0;
		ay = BREAKBRICK_GRAVITY;
		timer_die = GetTickCount64();
		// vx vy by angle
		float angleInRadian = angleInit * 3.14159f / 180.0f;
		vx = speed * cos(angleInRadian);
		vy = -speed * sin(angleInRadian);
	};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};