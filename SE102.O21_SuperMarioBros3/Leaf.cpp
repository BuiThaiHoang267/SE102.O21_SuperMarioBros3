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
	if (state == LEAF_STATE_UP && vy > 0)
	{
		SetState(LEAF_STATE_DOWN);
	}

	if (vy < -0.02  && state == LEAF_STATE_DOWN)
	{
		flexDirection = -flexDirection;
		vx = -vx;
		vy = LEAF_VY;
	}
}

void CLeaf::SetState(int state)
{
	this->state = state;
	if (state == LEAF_STATE_DOWN)
	{
		this->ax = 0;
		this->ay = LEAF_GRAVITY;
		this->flexDirection = 1;
		this->vx = LEAF_VX;
		this->vy = LEAF_VY;
	}
}