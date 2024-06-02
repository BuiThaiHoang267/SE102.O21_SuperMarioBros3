#include "GoombaJump.h"
#include "Turtle.h"
#include "Platform.h"
#include "debug.h"

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
	isOnPlatform = false;
};

void CGoombaJump::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoombaJump*>(e->obj)) return;
	if (dynamic_cast<CTurtle*>(e->obj)) return;


	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny == -1 && level == GOOMBAJUMP_LEVEL_WING && state == GOOMBAJUMP_STATE_JUMP)
		{
			//DebugOut(L"Cham dat %d\n", countJump);
			isOnPlatform = true;
		}
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

	if (state == GOOMBAJUMP_STATE_DIE_TORTOISESHELL)
	{
		y += vy * dt;
		x += vx * dt;
		if (GetTickCount64() - die_start > GOOMBAJUMP_DIE_TORTOISESHELL_TIMEOUT)
		{
			isDeleted = true;
		}
		return;
	}

	if ((state == GOOMBAJUMP_STATE_DIE) && (GetTickCount64() - die_start > GOOMBAJUMP_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	if (state == GOOMBAJUMP_STATE_JUMP && isOnPlatform == true)
	{
		if (countJump == 4)
		{
			SetState(GOOMBAJUMP_STATE_WALKING);
			countJump = 0;
		}
		else
		{
			SetState(GOOMBAJUMP_STATE_JUMP);	
		}
	}
	if ((state == GOOMBAJUMP_STATE_WALKING) && (GetTickCount64() - walk_start > 1000) && level == GOOMBAJUMP_LEVEL_WING)
	{
		SetState(GOOMBAJUMP_STATE_JUMP);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoombaJump::Render()
{
	aniId = GetAniId();
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
}

void CGoombaJump::SetState(int state)
{
	this->state = state;
	if (state == GOOMBAJUMP_STATE_JUMP)
	{
		countJump++;
		if (countJump == 4)
		{
			//DebugOut(L"jump max %d\n", countJump);
			vy = -GOOMBAJUMP_VY_JUMP_MAX;
		}
		else
		{
			//DebugOut(L"jump %d\n", countJump);
			vy = -GOOMBAJUMP_VY_JUMP;
		}
	}
	else if (state == GOOMBAJUMP_STATE_DIE)
	{
		die_start = GetTickCount64();
		y += (GOOMBAJUMP_BBOX_HEIGHT - GOOMBAJUMP_BBOX_HEIGHT_DIE) / 2 ;
		vy = 0;
		vx = 0;
		ax = 0;
		ay = 0;
	}
	else if (state == GOOMBAJUMP_STATE_WALKING)
	{
		if (level == GOOMBAJUMP_LEVEL_WING)
		{
			walk_start = GetTickCount64();
		}
		else
		{
			y -= 1;
		}
	}
	else if (state == GOOMBAJUMP_STATE_DIE_TORTOISESHELL)
	{
		die_start = GetTickCount64();
	}
}

int CGoombaJump::GetAniId()
{
	if (state == GOOMBAJUMP_STATE_WALKING)
	{
		if (level == GOOMBAJUMP_LEVEL_NORMAL)
		{
			return ID_ANI_GOOMBAJUMP_WALKING;
		}
		else
		{
			return ID_ANI_GOOMBAJUMP_WALKING_WING;
		}
	}
	else if (state == GOOMBAJUMP_STATE_DIE)
	{
		return ID_ANI_GOOMBAJUMP_DIE;
	}
	else if (state == GOOMBAJUMP_STATE_JUMP)
	{
		return ID_ANI_GOOMBAJUMP_JUMPING;
	}
	else if(GOOMBAJUMP_STATE_DIE_TORTOISESHELL)
	{
		return ID_ANI_GOOMBAJUMP_DIE_TORTOISESHELL;
	}
}

void CGoombaJump::SetLevel(int level)
{
	this->level = level;
}

int CGoombaJump::GetLevel()
{
	return this->level;
}

void CGoombaJump::DieFromTortoiseshell(int flexDirection)
{
	ax = 0;
	ay = GRAVITY_COLLIDER_TORTOISESHELL;
	vx = VX_COLLIDER_TORTOISESHELL * flexDirection;
	vy = -VY_COLLIDER_TORTOISESHELL;
	SetState(GOOMBAJUMP_STATE_DIE_TORTOISESHELL);
}