#include "Turtle.h"

void CTurtle::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(400000)->Render(x,y);
}

void CTurtle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TURTLE_BBOX_WIDTH / 2 + 1;
	t = y - TURTLE_BBOX_HEIGHT / 2;
	r = l + TURTLE_BBOX_WIDTH - 1;
	b = t + TURTLE_BBOX_HEIGHT;
}

int CTurtle::GetAniId()
{
	return 1;
}