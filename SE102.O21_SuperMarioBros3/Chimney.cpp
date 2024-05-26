#include "Chimney.h"

void CChimney::Render()
{
	if (typeChimney == 1)
	{
		CSprites* spirtes = CSprites::GetInstance();
		spirtes->Get(ID_SPRITE_CHIMNEY_TALL)->Draw(x, y);
	}
	else
	{
		CSprites* spirtes = CSprites::GetInstance();
		spirtes->Get(ID_SPRITE_CHIMNEY_SHORT)->Draw(x, y);
	}
	//RenderBoundingBox();
}

void CChimney::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (typeChimney == 1) {

		l = x - CHIMNEY_TALL_BBOX_WIDTH / 2 + 1;
		t = y - CHIMNEY_TALL_BBOX_HEIGHT / 2;
		r = l + CHIMNEY_TALL_BBOX_WIDTH - 1;
		b = t + CHIMNEY_TALL_BBOX_HEIGHT;
	}
	else 
	{
		l = x - CHIMNEY_SHORT_BBOX_WIDTH / 2 + 1;
		t = y - CHIMNEY_SHORT_BBOX_HEIGHT / 2;
		r = l + CHIMNEY_SHORT_BBOX_WIDTH - 1;
		b = t + CHIMNEY_SHORT_BBOX_HEIGHT;
	}
}