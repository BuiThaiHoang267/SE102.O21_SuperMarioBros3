#include "EffectCoinBox.h"
#include "PlayScene.h"
#include "EffectPoint.h"

void CEffectCoinBox::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COINBOX)->Render(x, y);

	//RenderBoundingBox();
}

void CEffectCoinBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - EF_COINBOX_WIDTH / 2;
	t = y - EF_COINBOX_HEIGHT / 2;
	r = l + EF_COINBOX_WIDTH - 1;
	b = t + EF_COINBOX_HEIGHT;
}

void CEffectCoinBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += COINBOX_GRAVITY * dt;
	y += vy * dt;
	if (y > posY) {
		if (!calledEffectPoint) {
			calledEffectPoint = true;
			EffectPoint();
		}
	}
	CGameObject::Update(dt, coObjects);
}

void CEffectCoinBox::EffectPoint() {
	if (calledEffectPoint = true) {
		LPGAMEOBJECT effectCoinBox = new CEffectPoint(x, y,100);
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		p->AddGameObject(effectCoinBox);

		this->Delete();
	}
}