#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define BUTTONP_STATE_IDLE 100
#define BUTTONP_STATE_CLICKED 200

#define	BUTTONP_WIDTH 16
#define BUTTONP_BBOX_WIDTH 16
#define BUTTONP_BBOX_HEIGHT 16

class CButtonP : public CGameObject {
protected:
	bool canClick;
public:
	CButtonP(float x, float y) : CGameObject(x, y) {
		SetState(BUTTONP_STATE_IDLE);
		this->canClick = true;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return canClick; }
	int IsCollidable() { return canClick; }
	void HandleClick();
};