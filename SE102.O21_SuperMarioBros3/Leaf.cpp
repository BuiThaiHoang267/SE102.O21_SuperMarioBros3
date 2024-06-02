#include "Leaf.h"

void CLeaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (flexDirection == 1)
	{
		animations->Get(ID_ANI_LEAF_RIGHT)->Render(x, y);
	}
	else
	{
		animations->Get(ID_ANI_LEAF_LEFT)->Render(x, y);
	}
}
void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}
void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx += ax * dt;
	vy += ay * dt;
	x += vx * dt;
	y += vy * dt;
	if (vy < 0)
	{
		flexDirection = -flexDirection;
		vx = -vx;
		vy = LEAF_VY;
	}
}