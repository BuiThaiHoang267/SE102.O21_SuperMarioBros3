#include "FlowerEnemy.h"

void CFlowerEnemy::Render()
{
	//if (isAnimation == 1)
	//{
	//	CAnimations* animations = CAnimations::GetInstance();
	//	animations->Get(ID_ANI_COIN)->Render(x, y);
	//}
	//else
	//{
	//	CSprites* spirtes = CSprites::GetInstance();
	//	spirtes->Get(ID_NOTANI_COIN)->Draw(x, y);
	//}

	switch (this->state)
	{
	case FLOWERENEMY_STATE_IDLE:
		{

		}
		break;
	case FLOWERENEMY_STATE_UP:
		{

		}
		break;
	case FLOWERENEMY_STATE_FIRE:
		{

		}
		break;
	case FLOWERENEMY_STATE_DOWN:
		{

		}
		break;
	default:
		break;
	}

}

void CFlowerEnemy::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	/*l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;*/
}

void CFlowerEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{

}

void CFlowerEnemy::SetState(int state)
{

}