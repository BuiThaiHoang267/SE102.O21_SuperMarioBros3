#include "FlowerEnemy.h"

void CFlowerEnemy::Render()
{
	switch (this->state)
	{
	case FLOWERENEMY_STATE_IDLE:
		{
			CSprites* spirtes = CSprites::GetInstance();
			spirtes->Get(ID_NOTANI_FLOWERENEMY_LEFT_LOW)->Draw(x, y);
		}
		break;
	case FLOWERENEMY_STATE_UP:
		{
			CAnimations* animations = CAnimations::GetInstance();
			animations->Get(ID_ANI_FLOWERENEMY_UPDOWN_LEFT_HIGH)->Render(x, y);
		}
		break;
	case FLOWERENEMY_STATE_FIRE:
		{
			CSprites* spirtes = CSprites::GetInstance();
			spirtes->Get(ID_NOTANI_FLOWERENEMY_LEFT_HIGH)->Draw(x, y);
		}
		break;
	case FLOWERENEMY_STATE_DOWN:
		{
			CAnimations* animations = CAnimations::GetInstance();
			animations->Get(ID_ANI_FLOWERENEMY_UPDOWN_LEFT_HIGH)->Render(x, y);
		}
		break;
	default:
		CSprites* spirtes = CSprites::GetInstance();
		spirtes->Get(ID_NOTANI_FLOWERENEMY_LEFT_LOW)->Draw(x, y);
		break;
	}
}

void CFlowerEnemy::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FLOWERENEMY_BBOX_WIDTH / 2;
	t = y - FLOWERENEMY_BBOX_HEIGHT / 2;
	r = l + FLOWERENEMY_BBOX_WIDTH;
	b = t + FLOWERENEMY_BBOX_HEIGHT;
}

void CFlowerEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	y += vy * dt;
	if (state == FLOWERENEMY_STATE_UP && y < posY - distanceY) {
		SetState(FLOWERENEMY_STATE_FIRE);
	}
	if (state == FLOWERENEMY_STATE_DOWN && y > posY) {
		SetState(FLOWERENEMY_STATE_IDLE);
	}
	if ((state == FLOWERENEMY_STATE_FIRE) && (GetTickCount64() - fire_start > 3000)) {
		SetState(FLOWERENEMY_STATE_DOWN);
	}
	if ((state == FLOWERENEMY_STATE_IDLE) && (GetTickCount64() - fire_start > 3000)) {
		SetState(FLOWERENEMY_STATE_UP);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFlowerEnemy::SetState(int state)
{
	this->state = state;
	if (state == FLOWERENEMY_STATE_IDLE) 
	{
		fire_start = GetTickCount64();
		vy = 0;
		y = posY;// cap nhat lai vi tri ban dau
	}
	else if (state == FLOWERENEMY_STATE_UP) {
		vy = FLOWERENEMY_VY_UP;
	}
	else if (state == FLOWERENEMY_STATE_FIRE) {
		fire_start = GetTickCount64();
		vy = 0;
		y = posY - distanceY;// cap nhat lai vi tri ban
	}
	else if (state == FLOWERENEMY_STATE_DOWN) {
		vy = -FLOWERENEMY_VY_UP;
	}
}

int CFlowerEnemy::GetIdAni() 
{
	if (state == FLOWERENEMY_STATE_UP)
	{
		if (isLeft) {
			return ID_ANI_FLOWERENEMY_UPDOWN_LEFT_HIGH;
		}
		else
		{
			return ID_ANI_FLOWERENEMY_UPDOWN_RIGHT_HIGH;
		}
	}
	else if (state == FLOWERENEMY_STATE_DOWN)
	{
		if (isLeft) {
			return ID_ANI_FLOWERENEMY_UPDOWN_LEFT_HIGH;
		}
		else
		{
			return ID_ANI_FLOWERENEMY_UPDOWN_RIGHT_HIGH;
		}
	}
	else if (state == FLOWERENEMY_STATE_FIRE)
	{
		if (isLeft && isHigh) 
		{
			return ID_NOTANI_FLOWERENEMY_LEFT_HIGH;
		}
		else if (isLeft && !isHigh)
		{
			return ID_NOTANI_FLOWERENEMY_LEFT_LOW;
		}
		else if (!isLeft && isHigh)
		{
			return ID_NOTANI_FLOWERENEMY_RIGHT_HIGH;
		}
		else {
			return ID_NOTANI_FLOWERENEMY_RIGHT_LOW;
		}
	}
	else {
		aniId = ID_NOTANI_FLOWERENEMY_LEFT_HIGH;
	}
}