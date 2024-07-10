#include "Block.h"

void CBlock::Render()
{
	RenderBoundingBox();
}

void CBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->width / 2 + 1;
	t = y - this->height / 2 + 1;
	r = l + this->width;
	b = t + this->height;
}