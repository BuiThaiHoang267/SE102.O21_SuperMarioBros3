#include "Raycast.h"
#include "Mario.h"
#include "debug.h"

void CRaycast::Render()
{
	RenderBoundingBox();
}

void CRaycast::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->width / 2;
	t = y - this->height / 2;
	r = l + this->width;
	b = t + this->height;
}

void CRaycast::OnCollisionWith(LPCOLLISIONEVENT e)
{
	DebugOut(L"[INFO] Khong va cham voi mario %d\n", 1);

	if (dynamic_cast<CMario*>(e->obj))
	{
		DebugOut(L"[INFO] va cham voi mario %d\n", 1);
		OnCollisionWithMario(e);
	}
}

void CRaycast::OnCollisionWithMario(LPCOLLISIONEVENT e)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", "va cham mario");
	CMario* mario = dynamic_cast<CMario*>(e->obj);
	float xm, ym;
	mario->GetPosition(xm, ym);
	isDetectedMario = true;
	//set isLeft
	if (xm < this->x) {
		isLeft = true;
	}
	else
	{
		isLeft = false;
	}
	//set isHigh
	if (ym < this->y)
	{
		isHigh = true;
	}
	else
	{
		isHigh = false;
	}
}

void CRaycast::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CRaycast::OnNoCollision(DWORD dt)
{
	
}

void CRaycast::OnTriggerEnter(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj)) 
	{
		DebugOut(L"[INFO] enter trigger mario %d\n", 1);
	}
}
void CRaycast::OnTriggerStay(LPCOLLISIONEVENT e) 
{
	if (dynamic_cast<CMario*>(e->obj))
	{
		DebugOut(L"[INFO] stay trigger mario %d\n", 1);
	}
}
void CRaycast::OnTriggerExit(LPGAMEOBJECT e)
{
	if (dynamic_cast<CMario*>(e))
	{
		DebugOut(L"[INFO] exit trigger mario %d\n", 1);	
	}
}