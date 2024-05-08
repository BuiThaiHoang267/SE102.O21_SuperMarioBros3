#include "GiftBox.h"
#include "Mario.h"

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
	SetState(GIFTBOX_STATE_OPENED);
	/*CMushroom* mushroom = new CMushroom(x, y);
	objects.push_front(mushroom);*/
}

//void CGiftBox::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//	if (dynamic_cast<CMario*>(e->obj))
//		OnCollisionWithMario(e);
//}
//
//void CGiftBox::OnCollisionWithMario(LPCOLLISIONEVENT e) 
//{
//	SetState(GIFTBOX_STATE_OPENED);
//}