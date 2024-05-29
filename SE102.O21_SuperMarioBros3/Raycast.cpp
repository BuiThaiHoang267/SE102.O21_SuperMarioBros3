#include "Raycast.h"
#include "Mario.h"
#include "debug.h"

void CRaycast::Render()
{
	//RenderBoundingBox();
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

	if (dynamic_cast<CMario*>(e->obj))
	{
		OnCollisionWithMario(e);
	}
}

void CRaycast::OnCollisionWithMario(LPCOLLISIONEVENT e)
{
	
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
		//DebugOut(L"[INFO] enter trigger mario %d\n", 1);
		isDetectedMario = true;
	}
}
void CRaycast::OnTriggerStay(LPCOLLISIONEVENT e) 
{
	if (dynamic_cast<CMario*>(e->obj))
	{
		isDetectedMario = true;
		dynamic_cast<CMario*>(e->obj)->GetPosition(posXMario, posYMario);
		//set isLeft
		if (posXMario < this->x) {
			isLeft = true;
		}
		else
		{
			isLeft = false;
		}
		//set isHigh
		if (posYMario < this->y)
		{
			isHigh = true;
		}
		else
		{
			isHigh = false;
		}
	}
}
void CRaycast::OnTriggerExit(LPGAMEOBJECT e)
{
	if (dynamic_cast<CMario*>(e))
	{
		//DebugOut(L"[INFO] exit trigger mario %d\n", 1);	
		isDetectedMario = false;
	}
}