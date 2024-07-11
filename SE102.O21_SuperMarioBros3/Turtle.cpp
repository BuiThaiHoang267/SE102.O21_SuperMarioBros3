#include "Turtle.h"
#include "GiftBox.h"
#include "debug.h"
#include "Goomba.h"
#include "GoombaJump.h"
#include "Brick.h"

void CTurtle::Render()
{
	aniId = GetAniId();
	CAnimations* animations = CAnimations::GetInstance();
	if (type > 0)
	{
		aniId += 10;
	}
	animations->Get(aniId)->Render(x,y);
	this->checkmove->Render();
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
	if (vy > TURTLE_VY_MAX_FALL)
	{
		vy = TURTLE_VY_MAX_FALL;
	}

	if (isOnPlatform && state == TURTLE_STATE_JUMP)
	{
		vy = TURTLE_VY_JUMP;
	}

	//update pos checkmove
	if (type == 0)
	{
		UpdatePosCheckMove();
		checkmove->Update(dt,coObjects);
	}
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
	if (state == TURTLE_STATE_MARIO_HOLD && GetTickCount64() - tortoiseshell_start > TURTLE_RETURN_TIMEOUT)
	{
		SetState(TURTLE_STATE_WAKEUP);
	}
	if (state == TURTLE_STATE_WAKEUP && GetTickCount64() - wakeup_start > TURTLE_WAKEUP_TIMEOUT)
	{
		SetState(TURTLE_STATE_WALK);
	}
	//if (state == TURTLE_STATE_TORTOISESHELL || state == TURTLE_STATE_WAKEUP)
	//{
	//	return;
	//}
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
	else if (state == TURTLE_STATE_JUMP)
	{
		if (vx <= 0)
			return ID_ANI_TURTLE_JUMP_LEFT;
		else
			return ID_ANI_TURTLE_JUMP_RIGHT;
	}
	else if (state == TURTLE_STATE_DIE)
	{
		return ID_ANI_TURTLE_DIE;
	}
	else {
		return ID_ANI_TURTLE_TORTOISESHELL;
	}
}

void CTurtle::OnCollisionWith(LPCOLLISIONEVENT e)
{
	OnCollisionWhenStateRun(e);
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CTurtle*>(e->obj)) return;


	if (e->ny < 0)
	{
		vy = 0;
		isOnPlatform = true;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		flexDirection = -flexDirection;
	}

	if (dynamic_cast<CGiftBox*>(e->obj))
	{
		CGiftBox* m = (CGiftBox*)e->obj;
		if (e->nx != 0 && state == TURTLE_STATE_RUN) {
			m->CanOpen();
		}
	}
}

void CTurtle::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
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
		vx = TURTLE_VX_STATE_WALK * flexDirection;
		ay = TURTLE_GRAVITY * 2;
	}
	else if (state == TURTLE_STATE_TORTOISESHELL)
	{
		if (statePre == TURTLE_STATE_WALK)
		{
			y += 4;
		}
		isStatic = true;
		tortoiseshell_start = GetTickCount64();
		offsetYBBox = 0;
		vx = 0;
		vy = -0.1;
	}
	else if (state == TURTLE_STATE_RUN)
	{
		y -= 2;
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
		//ay = 0;
	}
	else if (state == TURTLE_STATE_MARIO_HOLD)
	{
		vx = 0.0f;
		vy = 0.0f;
		ay = 0.0f;
		tortoiseshell_start = GetTickCount64();
	}
	else if (state == TURTLE_STATE_JUMP)
	{
		isStatic = false;
		offsetYBBox = 4;
		y -= 5;
		vx = TURTLE_VX_STATE_WALK * flexDirection;
		ay = TURTLE_GRAVITY;
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

void CTurtle::OnCollisionWhenStateRun(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsCollidable())
		return;

	if (state == TURTLE_STATE_RUN && e->obj->GetTag() == TAG_ENEMY)
	{
		int flexDirection = vx > 0? 1 :-1;
		if (dynamic_cast<CGoomba*>(e->obj))
		{
			dynamic_cast<CGoomba*>(e->obj)->DieFromTortoiseshell(flexDirection);
		}
		else if (dynamic_cast<CGoombaJump*>(e->obj))
		{
			dynamic_cast<CGoombaJump*>(e->obj)->DieFromTortoiseshell(flexDirection);
		}
		else if (dynamic_cast<CTurtle*>(e->obj))
		{
			dynamic_cast<CTurtle*>(e->obj)->Die(flexDirection);
		}
	}

	if (dynamic_cast<CBrick*>(e->obj) && state == TURTLE_STATE_RUN)
	{
		if (e->ny == 0 && e->nx != 0)
		{
			dynamic_cast<CBrick*>(e->obj)->CanOpen(2);	
		}
	}
}

void CTurtle::Die(int direction)
{
	SetState(TURTLE_STATE_DIE);
	vx = TURTLE_VX_DIE * direction;
	vy = TURTLE_VY_DIE;
	ay = TURTLE_GRAVITY;
	isBlock = 0;
}