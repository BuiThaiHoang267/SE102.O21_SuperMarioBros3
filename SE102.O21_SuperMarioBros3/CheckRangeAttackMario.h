#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CCheckRangeAttackMario : public CGameObject {
protected:
	int height;
	int width;
	bool canAttack;
public:
	CCheckRangeAttackMario(float x, float y, int widthh, int heightt) : CGameObject(x, y)
	{
		this->width = widthh;
		this->height = heightt;
		canAttack = false;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	bool GetCanAttack() { return this->canAttack; }
	void SetCanAttack(bool canAtc) { this->canAttack = canAtc; }
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }
	void OnTriggerEnter(LPCOLLISIONEVENT e);
	void OnTriggerStay(LPCOLLISIONEVENT e);
	void OnTriggerExit(LPGAMEOBJECT e);
};