#include "Turtle.h"
#include "GiftBox.h"
#include "debug.h"
#include "Goomba.h"

void CTurtle::Render()
{
	aniId = GetAniId();
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x,y);
	this->checkmove->Render();
}

int CTurtle::IsStatic()
{
	return isStatic;
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

	//update pos checkmove
	UpdatePosCheckMove();
	checkmove->Update(dt,coObjects);
	//

	if (state == TURTLE_STATE_WALK && checkmove->isOnPlatform == false)
	{
		vx = -vx;
		checkmove->isOnPlatform = true;
	}

	if (state == TURTLE_STATE_TORTOISESHELL && GetTickCount64() - tortoiseshell_start > TURTLE_RETURN_TIMEOUT)
	{
		SetState(TURTLE_STATE_WAKEUP);
	}

	if (state == TURTLE_STATE_WAKEUP && GetTickCount64() - wakeup_start > TURTLE_WAKEUP_TIMEOUT)
	{
		SetState(TURTLE_STATE_WALK);
	}
	if (state == TURTLE_STATE_TORTOISESHELL || state == TURTLE_STATE_WAKEUP)
	{
		return;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTurtle::UpdatePosCheckMove()
{
	if (vx > 0)
	{
		checkmove->SetPosition(x + OFFSET_CHECKMOVE_X, y + OFFSET_CHECKMOVE_Y);
	}
	else
	{
		checkmove->SetPosition(x - OFFSET_CHECKMOVE_X, y + OFFSET_CHECKMOVE_Y);
	}
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
	if (dynamic_cast<CGoomba*>(e->obj)) return;


	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}

	if (dynamic_cast<CGiftBox*>(e->obj))
	{
		CGiftBox* m = (CGiftBox*)e->obj;
		if (e->nx != 0) {
			m->CanOpen();
		}
	}
}

void CTurtle::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CTurtle::SetState(int state)
{
	int statePre = this->state;
	this->state = state;
	if (state == TURTLE_STATE_WALK)
	{
		isStatic = false;
		offsetYBBox = 4;
		y -= 5;
		vx = -TURTLE_VX_STATE_WALK;
		ay = TURTLE_GRAVITY;
	}
	else if (state == TURTLE_STATE_TORTOISESHELL)
	{
		if (statePre == TURTLE_STATE_WALK)
		{
			y += 3;
		}
		isStatic = true;
		tortoiseshell_start = GetTickCount64();
		offsetYBBox = 0;
		vx = 0;
		vy = 0;
		ay = 0;
	}
	else if (state == TURTLE_STATE_RUN)
	{
		isStatic = false;
		offsetYBBox = 0;
		vy = 0;
	}
	else if (state == TURTLE_STATE_WAKEUP)
	{
		isStatic = true;
		wakeup_start = GetTickCount64();
		offsetYBBox = 0;
		vx = 0;
		vy = 0;
		ay = 0;
	}
}

void CTurtle::SetDirectionRun(int direction)
{
	if (direction == 1)
	{
		vx = TURTLE_VX_STATE_RUN;
		ay = TURTLE_GRAVITY;
	}
	else
	{
		vx = -TURTLE_VX_STATE_RUN;
		ay = TURTLE_GRAVITY;
	}
}