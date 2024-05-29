#include "Turtle.h"

void CTurtle::Render()
{
	aniId = GetAniId();
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x,y);
	//RenderBoundingBox();
}

void CTurtle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TURTLE_BBOX_WIDTH / 2 + 1;
	t = y - TURTLE_BBOX_HEIGHT / 2 + offsetYBBox;
	r = l + TURTLE_BBOX_WIDTH - 1;
	b = t + TURTLE_BBOX_HEIGHT;
}

void CTurtle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	if (state == TURTLE_STATE_TORTOISESHELL && GetTickCount64() - tortoiseshell_start > TURTLE_RETURN_TIMEOUT)
	{
		SetState(TURTLE_STATE_WAKEUP);
	}

	if (state == TURTLE_STATE_WAKEUP && GetTickCount64() - wakeup_start > TURTLE_WAKEUP_TIMEOUT)
	{
		SetState(TURTLE_STATE_WALK);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

int CTurtle::GetAniId()
{
	if (state == TURTLE_STATE_WALK)
	{
		if (vx <= 0)
			return ID_ANI_TURTLE_WALK_LEFT;
		else
			return ID_ANI_TURTLE_WALK_RIGHT;
	}
	else if (state == TURTLE_STATE_TORTOISESHELL)
	{
		return ID_ANI_TURTLE_TORTOISESHELL;
	}
	else if (state == TURTLE_STATE_RUN)
	{
		if (vx <= 0)
			return ID_ANI_TURTLE_RUN_LEFT;
		else
			return ID_ANI_TURTLE_RUN_RIGHT;
	}
	else if (state == TURTLE_STATE_WAKEUP)
	{
		return ID_ANI_TURTLE_WAKEUP;
	}
	else {
		return ID_ANI_TURTLE_TORTOISESHELL;
	}
}

void CTurtle::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CTurtle*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CTurtle::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CTurtle::SetState(int state)
{
	this->state = state;
	if (state == TURTLE_STATE_WALK)
	{
		offsetYBBox = 4;
		y -= 4;
		vx = TURTLE_VX_STATE_WALK;
		ay = TURTLE_GRAVITY;
	}
	else if (state == TURTLE_STATE_TORTOISESHELL)
	{
		y += 4;
		tortoiseshell_start = GetTickCount64();
		offsetYBBox = 0;
		vx = 0;
	}
	else if (state == TURTLE_STATE_RUN)
	{
		offsetYBBox = 0;
		vx = TURTLE_VX_STATE_RUN;
	}
	else if (state == TURTLE_STATE_WAKEUP)
	{
		wakeup_start = GetTickCount64();
		offsetYBBox = 0;
		vx = 0;
		vy = 0;
		ay = 0;
	}
}