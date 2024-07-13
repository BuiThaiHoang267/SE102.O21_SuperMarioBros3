#include "PanelUI.h"
#include "PlayScene.h"
#include "debug.h"

void CPanelUI::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteId)->Draw(x, y);
	//RenderBoundingBox();
}

void CPanelUI::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->width / 2 + 1;
	t = y - this->height / 2 + 1;
	r = l + this->width;
	b = t + this->height;
}


void CPanelUI::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isInitUI)
	{
		this->InitUI();
	}
	CGameObject::Update(dt, coObjects);
}

void CPanelUI::InitUI()
{
	isInitUI = true;
	LPSCENE s = CGame::GetInstance()->GetCurrentScene();
	CPlayScene* p = dynamic_cast<CPlayScene*>(s);
	for (int i = 0; i < 3; i++)
	{
		LPGAMEOBJECT numtext = new CNumberText(x, y);
		p->AddGameObjectPushBack(numtext);
		timer.push_back(numtext);
	}
	for (int i = 0; i < 2; i++)
	{
		LPGAMEOBJECT numtext = new CNumberText(x, y);
		p->AddGameObjectPushBack(numtext);
		coins.push_back(numtext);
	}
	for (int i = 0; i < 7; i++)
	{
		LPGAMEOBJECT numtext = new CNumberText(x, y);
		p->AddGameObjectPushBack(numtext);
		points.push_back(numtext);
	}
	for (int i = 0; i < 2; i++)
	{
		LPGAMEOBJECT numtext = new CNumberText(x, y);
		p->AddGameObjectPushBack(numtext);
		lifes.push_back(numtext);
	}
	for (int i = 0; i < 1; i++)
	{
		LPGAMEOBJECT numtext = new CNumberText(x, y);
		CNumberText* temp = dynamic_cast<CNumberText*>(numtext);
		temp->SetIdSprite(540000);
		p->AddGameObjectPushBack(numtext);
		energy.push_back(numtext);
	}
}

void CPanelUI::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	if (timer.size() > 0)
	{
		for (int i = 0; i < timer.size(); i++)
		{
			timer[i]->SetPosition(x + i * 8 + 10, y - 4);
		}
	}
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i]->SetPosition(x + i * 8 + 18, y - 12);
	}
	for (int i = 0; i < points.size(); i++)
	{
		points[i]->SetPosition(x + i * 8 -64, y - 4);
	}
	for (int i = 0; i < lifes.size(); i++)
	{
		lifes[i]->SetPosition(x + i * 8 - 86, y - 4);
	}
	for (int i = 0; i < energy.size(); i++)
	{
		energy[i]->SetPosition(x + i * 8 - 36, y - 12);
	}
}