#include "GoombaJump.h"
#include "Turtle.h"


void CGoombaJump::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBAJUMP_STATE_DIE)
	{
		left = x - GOOMBAJUMP_BBOX_WIDTH / 2;
		top = y - GOOMBAJUMP_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBAJUMP_BBOX_WIDTH;
		bottom = top + GOOMBAJUMP_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - GOOMBAJUMP_BBOX_WIDTH / 2;
		top = y - GOOMBAJUMP_BBOX_HEIGHT / 2;
		right = left + GOOMBAJUMP_BBOX_WIDTH;
		bottom = top + GOOMBAJUMP_BBOX_HEIGHT;
	}
}

void CGoombaJump::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoombaJump::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoombaJump*>(e->obj)) return;
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

void CGoombaJump::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == GOOMBAJUMP_STATE_DIE) && (GetTickCount64() - die_start > GOOMBAJUMP_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoombaJump::Render()
{
	
}

void CGoombaJump::SetState(int state)
{
	
}
