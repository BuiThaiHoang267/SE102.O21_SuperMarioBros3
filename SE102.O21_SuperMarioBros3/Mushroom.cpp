#include "Mushroom.h"
#include "Goomba.h"
#include "Mario.h"
#include "PlayScene.h"
#include "EffectPoint.h"
#include "Turtle.h"

CMushroom::CMushroom(float x, float y, int type) : CGameObject(x, y) {
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	this->typeMushroom = type;
	walk_start = -1;
	SetState(MUSHROOM_STATE_VISIBILITY);
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vx += ax * dt;
	vy += ay * dt;

	if ((state == MUSHROOM_STATE_VISIBILITY) && (GetTickCount64() - walk_start > MUSROOM_TIMEOUT_VISIBILITY)) {
		SetState(MUSHROOM_STATE_WALKING);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::Render() {
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_ANI_MUSHROOM+typeMushroom)->Draw(x, y);

	//RenderBoundingBox();
}

void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x - MUSHROOM_BBOX_WIDTH / 2 + 1;
	t = y - MUSHROOM_BBOX_HEIGHT / 2;
	r = l + MUSHROOM_BBOX_WIDTH - 1;
	b = t + MUSHROOM_BBOX_HEIGHT - 1;
}

void CMushroom::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<CMario*>(e->obj)) return;
	if (dynamic_cast<CTurtle*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CMushroom::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_VISIBILITY:
		walk_start = GetTickCount64();
		vy = -0.01f;
		ay = 0;
		break;
	case MUSHROOM_STATE_WALKING:
		vx = -MUSHROOM_WALKING_SPEED;
		ay = MUSHROOM_GRAVITY;
		break;
	}
}

void CMushroom::OnCollisionWithMario(float mx, float my)
{
	if (state != MUSHROOM_STATE_DIE)
	{
		state = MUSHROOM_STATE_DIE;
		int point;
		if (typeMushroom == 1)
			point = 10;
		else
			point = 1000;
		LPGAMEOBJECT effectCoinBox = new CEffectPoint(mx, my, point);
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		p->AddGameObject(effectCoinBox);
		this->Delete();
	}
}