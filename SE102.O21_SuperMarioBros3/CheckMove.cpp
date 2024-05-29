#include "CheckMove.h"
#include "debug.h"

void CCheckMove::Render()
{
	//RenderBoundingBox();
}
void CCheckMove::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CCheckMove::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->width / 2;
	t = y - this->height / 2;
	r = l + this->width;
	b = t + this->height;
}
void CCheckMove::OnNoCollision(DWORD dt)
{
	y += vy * dt;
	isOnPlatform = false;
	//DebugOut(L"[INFO] no collision %d\n", 1);	
}
void CCheckMove::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
		isOnPlatform = true;
		//DebugOut(L"[INFO] on collision %d\n", 1);
	}
}
