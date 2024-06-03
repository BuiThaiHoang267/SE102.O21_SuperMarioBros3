#include "Goomba.h"
#include "Turtle.h"
#include "EffectPoint.h"
#include "PlayScene.h"

CGoomba::CGoomba(float x, float y):CGameObject(x, y)
{
	this->tag = TAG_ENEMY;
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 
	if (dynamic_cast<CTurtle*>(e->obj)) return;


	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (state == GOOMBA_STATE_DIE_TORTOISESHELL)
	{
		y += vy * dt;
		x += vx * dt;
		if (GetTickCount64() - die_start > GOOMBA_DIE_TORTOISESHELL_TIMEOUT)
		{
			isDeleted = true;
		}
		return;
	}

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE) 
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	else if (state == GOOMBA_STATE_DIE_TORTOISESHELL)
	{
		aniId = ID_ANI_GOOMBA_DIE_TORTOISESHELL;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_DIE_TORTOISESHELL:
			die_start = GetTickCount64();
	}
}

void CGoomba::DieFromTortoiseshell(int flexDirection)
{
	if (state != GOOMBA_STATE_DIE_TORTOISESHELL)
	{
		ax = 0;
		ay = GRAVITY_COLLIDER_TORTOISESHELL;
		vx = VX_COLLIDER_TORTOISESHELL * flexDirection;
		vy = -VY_COLLIDER_TORTOISESHELL;
		LPGAMEOBJECT effectCoinBox = new CEffectPoint(x, y - 16, 100);
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		p->AddGameObject(effectCoinBox);
		SetState(GOOMBA_STATE_DIE_TORTOISESHELL);
	}
}
