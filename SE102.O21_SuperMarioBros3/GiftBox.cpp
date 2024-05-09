#include "GiftBox.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Mushroom.h"

void CGiftBox::Render() {
	int aniId = ID_ANI_GIFTBOX_IDLE;
	if (state == GIFTBOX_STATE_OPENED)
	{
		aniId = ID_ANI_GIFTBOX_OPENED;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CGiftBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GIFTBOX_BBOX_WIDTH / 2 + 1;
	t = y - GIFTBOX_BBOX_HEIGHT / 2;
	r = l + GIFTBOX_BBOX_WIDTH -1 ;
	b = t + GIFTBOX_BBOX_HEIGHT;
}

void CGiftBox::OpenGiftBox() 
{
	LPGAMEOBJECT mushroom = new CMushroom(x, y);
	LPSCENE s = CGame::GetInstance()->GetCurrentScene();
	LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
	p->AddGameObject(mushroom);
}

void CGiftBox::CanOpen() {
	if (state == GIFTBOX_STATE_OPENED || state == GIFTBOX_STATE_BEFORE_OPENED)
		return;
	SetState(GIFTBOX_STATE_BEFORE_OPENED);
	vy = -0.2f;
}

void CGiftBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == GIFTBOX_STATE_BEFORE_OPENED)
	{
		vy += GIFTBOX_GRAVITY * dt;
		y += vy * dt;
	}
	if (y > posY && state == GIFTBOX_STATE_BEFORE_OPENED) {
		SetState(GIFTBOX_STATE_OPENED);
		y = posY;
		vy = 0;
		OpenGiftBox();
	}
	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}



