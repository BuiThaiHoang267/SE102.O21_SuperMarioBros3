#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_TURTLE_IDLE 430000

#define ID_ANI_TURTLE_WALK_LEFT 400000
#define ID_ANI_TURTLE_WALK_RIGHT 410000

#define ID_ANI_TURTLE_RUN_LEFT 400001
#define ID_ANI_TURTLE_RUN_RIGHT 410001

#define ID_ANI_TURTLE_WAKEUP_LEFT 420000

#define TURTLE_BBOX_WIDTH 16
#define TURTLE_BBOX_HEIGHT 16

class CTurtle : public CGameObject {
public:
	CTurtle(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
	int IsCollidable() { return 1; };
	int GetAniId();
};