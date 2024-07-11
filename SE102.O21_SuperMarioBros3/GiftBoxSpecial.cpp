#include "GiftBoxSpecial.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "EffectCoinBox.h"

void CGiftBoxSpecial::Render() {
	int aniId = GetAniId();
	CSprites::GetInstance()->Get(aniId)->Draw(x, y);
}

void CGiftBoxSpecial::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GIFTBOX_BBOX_WIDTH / 2 + 1;
	t = y - GIFTBOX_BBOX_HEIGHT / 2;
	r = l + GIFTBOX_BBOX_WIDTH - 1;
	b = t + GIFTBOX_BBOX_HEIGHT;
}

void CGiftBoxSpecial::OpenGiftBox()
{
	
}

void CGiftBoxSpecial::CanOpen()
{
	
}

void CGiftBoxSpecial::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - timer_rotate > TIMER_ROTATE)
	{
		timer_rotate = GetTickCount64();
		this->state = this->state + 1;
		if (this->state >= 3)
		{
			this->state = 0;
		}
	}
	
	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}

int CGiftBoxSpecial::GetAniId()
{
	if (state == GIFTBOX_SPECIAL_STATE_MUSHROOM)
	{
		return ID_ANI_MUSHROOM;
	}
	else if (state == GIFTBOX_SPECIAL_STATE_STAR)
	{
		return ID_ANI_STAR;
	}
	else
		return ID_ANI_FLOWERBLUE;
}
