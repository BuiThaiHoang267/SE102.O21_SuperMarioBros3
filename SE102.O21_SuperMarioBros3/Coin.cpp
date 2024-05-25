#include "Coin.h"

void CCoin::Render()
{
	if (isAnimation == 1) 
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_COIN)->Render(x, y);
	}
	else 
	{
		CSprites* spirtes = CSprites::GetInstance();
		spirtes->Get(ID_NOTANI_COIN)->Draw(x, y);
	}
	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}