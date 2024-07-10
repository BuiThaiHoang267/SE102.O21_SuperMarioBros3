#include "ButtonP.h"

void CButtonP::Render()
{
	if (state == BUTTONP_STATE_IDLE)
	{
		CAnimations* animations = CAnimations::GetInstance();
		//animations->Get(ID_ANI_COIN)->Render(x, y);
	}
	else
	{
		CSprites* spirtes = CSprites::GetInstance();
		//spirtes->Get(ID_NOTANI_BUTTONP)->Draw(x, y);
	}
	//RenderBoundingBox();
}

void CButtonP::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BUTTONP_BBOX_WIDTH / 2;
	t = y - BUTTONP_BBOX_HEIGHT / 2;
	r = l + BUTTONP_BBOX_WIDTH;
	b = t + BUTTONP_BBOX_HEIGHT;
}

void CButtonP::HandleClick()
{
	SetState(BUTTONP_STATE_CLICKED);
	canClick = false;
}