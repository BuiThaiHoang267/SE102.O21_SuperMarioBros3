#include "FlowerEnemy.h"
#include "PlayScene.h"
#include "Bullet.h"

void CFlowerEnemy::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	CSprites* s = CSprites::GetInstance();
	aniId = this->GetIdAni();
	if (type > 0)
	{
		aniId += 10;
	}
	if (state == FLOWERENEMY_STATE_IDLE || state == FLOWERENEMY_STATE_FIRE)
	{
		if (type == 1)
		{
			animations->Get(aniId)->Render(x, y);
		}
		else
		{
			s->Get(aniId)->Draw(x, y);
		}
	}
	else {
		animations->Get(aniId)->Render(x, y);
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
	shootRange->SetPosition(this->x, this->y);
	checkActivity->SetPosition(this->x, this->y + offsetYCheckActivity);
	if (state == FLOWERENEMY_STATE_IDLE)
	{
		CCheckActivity* check = dynamic_cast<CCheckActivity*>(checkActivity);
		if (check->GetIsDetectedMario())
		{
			fire_start = GetTickCount64();
			return;
		}
	}
	y += vy * dt;
	if (state == FLOWERENEMY_STATE_UP && y < posY - distanceY) {
		SetState(FLOWERENEMY_STATE_FIRE);
	}
	if (state == FLOWERENEMY_STATE_DOWN && y > posY) {
		SetState(FLOWERENEMY_STATE_IDLE);
	}
	if ((state == FLOWERENEMY_STATE_FIRE) && (GetTickCount64() - fire_start > 2000)) {
		SetState(FLOWERENEMY_STATE_DOWN);
	}
	if ((state == FLOWERENEMY_STATE_IDLE) && (GetTickCount64() - fire_start > 2000)) {
		SetState(FLOWERENEMY_STATE_UP);
	}
	if ((state == FLOWERENEMY_STATE_FIRE) && isFired == false && (GetTickCount64() - fire_start > 1000))
	{
		isFired = true;
		CRaycast* range = dynamic_cast<CRaycast*>(shootRange);
		if (range->GetIsDetectedMario() && type != 1) 
		{
			LPGAMEOBJECT bullet = new CBullet(x, y - 8, range->GetPosXMario(),range->GetPosYMario());
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
			p->AddGameObjectPushBack(bullet);
		}
	}

	

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFlowerEnemy::SetState(int state)
{
	this->state = state;
	if (state == FLOWERENEMY_STATE_IDLE) 
	{
		isFired = false;
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
	CRaycast* range = dynamic_cast<CRaycast*>(shootRange);
	if (range->GetIsDetectedMario())
	{
		this->isLeft = range->GetIsLeft();
		this->isHigh = range->GetIsHigh();
	}
	
	if (type == 1)
	{
		return ID_ANI_FLOWERENEMY_NOT_FIER;
	}

	if (state == FLOWERENEMY_STATE_UP)
	{
		if (isLeft && isHigh) {
			return ID_ANI_FLOWERENEMY_UPDOWN_LEFT_HIGH;
		}
		else if(isLeft && !isHigh)
		{
			return ID_ANI_FLOWERENEMY_UPDOWN_LEFT_LOW;
		}
		else if (!isLeft && isHigh)
		{
			return ID_ANI_FLOWERENEMY_UPDOWN_RIGHT_HIGH;
		}
		else 
		{
			return ID_ANI_FLOWERENEMY_UPDOWN_RIGHT_LOW;
		}
	}
	else if (state == FLOWERENEMY_STATE_DOWN)
	{
		if (isLeft && isHigh) {
			return ID_ANI_FLOWERENEMY_UPDOWN_LEFT_HIGH;
		}
		else if (isLeft && !isHigh)
		{
			return ID_ANI_FLOWERENEMY_UPDOWN_LEFT_LOW;
		}
		else if (!isLeft && isHigh)
		{
			return ID_ANI_FLOWERENEMY_UPDOWN_RIGHT_HIGH;
		}
		else
		{
			return ID_ANI_FLOWERENEMY_UPDOWN_RIGHT_LOW;
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
		return ID_NOTANI_FLOWERENEMY_LEFT_HIGH;
	}
}