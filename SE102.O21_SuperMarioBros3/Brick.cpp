#include "Brick.h"
#include "Coin.h"
#include "PlayScene.h"
#include "ButtonP.h"
#include "Mushroom.h"
#include "EffectBreakBrick.h"

void CBrick::Render()
{
	if (state == BRICK_STATE_OPENED) 
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_BRICK_OPENED)->Render(x, y);
	}
	else
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_BRICK)->Render(x, y);
	}
	
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2 + 1;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH - 1;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::Break()
{
	LPSCENE s = CGame::GetInstance()->GetCurrentScene();
	LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
	LPGAMEOBJECT ef1 = new CEffectBreakBrick(x, y, 0.2f, 60);
	LPGAMEOBJECT ef2 = new CEffectBreakBrick(x, y, 0.2f, 120);
	LPGAMEOBJECT ef3 = new CEffectBreakBrick(x, y, 0.15f, -30);
	LPGAMEOBJECT ef4 = new CEffectBreakBrick(x, y, 0.15f, -150);
	p->AddGameObjectPushBack(ef1);
	p->AddGameObjectPushBack(ef2);
	p->AddGameObjectPushBack(ef3);
	p->AddGameObjectPushBack(ef4);
	this->Delete();
}

void CBrick::OpenCoin()
{
	LPSCENE s = CGame::GetInstance()->GetCurrentScene();
	LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
	if (this == nullptr || this->IsDeleted())
	{
		return;
	}
	LPGAMEOBJECT coin = new CCoin(x, y, 0);
	p->AddGameObject(coin);
	this->Delete();
}

void CBrick::OpenMushroom()
{
	LPSCENE s = CGame::GetInstance()->GetCurrentScene();
	LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
	LPGAMEOBJECT mushroom = new CMushroom(x, y, 1);
	p->AddGameObject(mushroom);
}

void CBrick::CanOpen(int levelMario) {
	if (state == BRICK_STATE_OPENED || state == BRICK_STATE_BEFORE_OPENED)
		return;

	// type special
	if (typeBrick == BRICK_TYPE_SPECIAL && levelMario > 1) 
	{
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		LPGAMEOBJECT buttonP = new CButtonP(x, y - 16);
		p->AddGameObject(buttonP);
	}

	// type normal and mushroom
	if (levelMario > 1)
	{
		this->canOpen = true;
		if (typeBrick == 0)
		{
			Break();
			return;
		}
	}

	SetState(BRICK_STATE_BEFORE_OPENED);
	vy = -0.2f;
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == BRICK_STATE_BEFORE_OPENED)
	{
		vy += BRICK_GRAVITY * dt;
		y += vy * dt;
	}
	if (y > posY && state == BRICK_STATE_BEFORE_OPENED) {
		if (canOpen) {
			SetState(BRICK_STATE_OPENED);
			if (typeBrick == BRICK_TYPE_MUSHROOM)
			{
				OpenMushroom();
			}
		}
		else {
			SetState(BRICK_STATE_IDLE);
		}
		y = posY;
		vy = 0;
	}
	CGameObject::Update(dt, coObjects);
}