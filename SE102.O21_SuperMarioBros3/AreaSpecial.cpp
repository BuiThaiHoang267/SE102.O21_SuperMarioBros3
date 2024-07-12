#include "AreaSpecial.h"

void CAreaSpecial::Render()
{
	//RenderBoundingBox();
}
void CAreaSpecial::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x = posX;
	y = posY;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CAreaSpecial::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->width / 2;
	t = y - this->height / 2;
	r = l + this->width;
	b = t + this->height;
}