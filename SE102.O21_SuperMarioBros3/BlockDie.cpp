#include "BlockDie.h"
#include "Goomba.h"
#include "GoombaJump.h"
#include "Turtle.h"
#include "Mario.h"

void CBlockDie::Render()
{
	RenderBoundingBox();
}

void CBlockDie::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y - this->height / 2 + 1;
	r = l + this->width;
	b = t + this->height;
}

void CBlockDie::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (
		dynamic_cast<CGoomba*>(e->obj)
		|| dynamic_cast<CGoombaJump*>(e->obj)
		|| dynamic_cast<CTurtle*>(e->obj)
		) {
		e->obj->Delete();
	}
	else return;
}

void CBlockDie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x = posX;
	y = posY;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBlockDie::OnTriggerStay(LPCOLLISIONEVENT e) 
{
	if (
		dynamic_cast<CGoomba*>(e->obj)
		|| dynamic_cast<CGoombaJump*>(e->obj)
		|| dynamic_cast<CTurtle*>(e->obj)
		) {
		e->obj->Delete();
	}
	else return;
};