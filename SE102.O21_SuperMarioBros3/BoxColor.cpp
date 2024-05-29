#include "BoxColor.h"

void CBoxColor::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteId)->Draw(x, y);

	//RenderBoundingBox();
}

void CBoxColor::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->width / 2 + 1;
	t = y - this->height / 2 + 1;
	r = l + this->width - this->paddingRight - 1;
	b = t + this->height;
}

int CBoxColor::IsDirectionColliable(float nx, float ny)
{
	if (nx == 0 && ny == -1) return 1;
	else return 0;
}