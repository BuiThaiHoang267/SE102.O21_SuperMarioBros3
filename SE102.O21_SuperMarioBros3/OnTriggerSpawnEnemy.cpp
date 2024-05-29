#include "OnTriggerSpawnEnemy.h"

void COnTriggerSpawnEnemy::Render()
{
	RenderBoundingBox();
}
void COnTriggerSpawnEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void COnTriggerSpawnEnemy::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->width / 2;
	t = y - this->height / 2;
	r = l + this->width;
	b = t + this->height;
}
void COnTriggerSpawnEnemy::OnTriggerEnter(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj))
	{
		isDetectedMario = true;
	}
}
void COnTriggerSpawnEnemy::OnTriggerStay(LPCOLLISIONEVENT e)
{

}
void COnTriggerSpawnEnemy::OnTriggerExit(LPGAMEOBJECT e)
{
	if (dynamic_cast<CMario*>(e))
	{
		isDetectedMario = false;
	}
}
