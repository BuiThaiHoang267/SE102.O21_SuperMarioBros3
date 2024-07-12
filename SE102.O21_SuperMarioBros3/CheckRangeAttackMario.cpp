#include "CheckRangeAttackMario.h"
#include "debug.h"
#include "Brick.h"
#include "Goomba.h"
#include "GoombaJump.h"
#include "Turtle.h"
#include "GiftBox.h"

void CCheckRangeAttackMario::Render()
{
	//RenderBoundingBox();
}
void CCheckRangeAttackMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CCheckRangeAttackMario::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->width / 2;
	t = y - this->height / 2;
	r = l + this->width;
	b = t + this->height;
}
void CCheckRangeAttackMario::OnTriggerEnter(LPCOLLISIONEVENT e)
{
	
}
void CCheckRangeAttackMario::OnTriggerStay(LPCOLLISIONEVENT e)
{
	if (!canAttack)
		return;

	if (dynamic_cast<CBrick*>(e->obj))
	{
		CBrick* br = dynamic_cast<CBrick*>(e->obj);
		br->CanOpen(2);
	}
	else if (dynamic_cast<CGoomba*>(e->obj))
	{
		dynamic_cast<CGoomba*>(e->obj)->DieFromTortoiseshell(0);
	}
	else if (dynamic_cast<CGoombaJump*>(e->obj))
	{
		dynamic_cast<CGoombaJump*>(e->obj)->DieFromTortoiseshell(0);
	}
	else if (dynamic_cast<CTurtle*>(e->obj))
	{
		dynamic_cast<CTurtle*>(e->obj)->Die(0);
	}
	else if (dynamic_cast<CGiftBox*>(e->obj))
	{
		dynamic_cast<CGiftBox*>(e->obj)->CanOpen();
	}
	else
	{
		return;
	}
}
void CCheckRangeAttackMario::OnTriggerExit(LPGAMEOBJECT e)
{
	
}
