#include "CheckActivity.h"
#include "Mario.h"

void CCheckActivity::Render() 
{
	//RenderBoundingBox();
}
void CCheckActivity::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CCheckActivity::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->width / 2;
	t = y - this->height / 2;
	r = l + this->width;
	b = t + this->height;
}
void CCheckActivity::OnTriggerEnter(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj))
	{
		isDetectedMario = true;
	}
}
void CCheckActivity::OnTriggerStay(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj))
	{
		isDetectedMario = true;
	}
}
void CCheckActivity::OnTriggerExit(LPGAMEOBJECT e)
{
	if (dynamic_cast<CMario*>(e))
	{
		isDetectedMario = false;
	}
}