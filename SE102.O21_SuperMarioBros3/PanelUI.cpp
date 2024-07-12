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
	
	//CGameObject::Update(dt, coObjects);
}