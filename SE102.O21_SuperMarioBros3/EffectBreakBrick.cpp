#include "EffectBreakBrick.h"

void CEffectBreakBrick::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_ANI_BREAK_BRICK)->Draw(x, y);
}
void CEffectBreakBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx += ax * dt;
	vy += ay * dt;
	x += vx * dt;
	y += vy * dt;

	// 5s die
	if (GetTickCount64() - timer_die > TIMER_DIE_BREAKBRICK)
	{
		this->Delete();
	}
}
void CEffectBreakBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - EF_BREAKBRICK_WIDTH / 2;
	t = y - EF_BREAKBRICK_HEIGHT / 2;
	r = l + EF_BREAKBRICK_WIDTH - 1;
	b = t + EF_BREAKBRICK_HEIGHT;
}