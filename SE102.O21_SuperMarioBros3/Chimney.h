#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_SPRITE_CHIMNEY_TALL 300000
#define ID_SPRITE_CHIMNEY_SHORT 300001
#define ID_SPRITE_CHIMNEY_MID 300002

#define CHIMNEY_TALL_BBOX_WIDTH 30
#define CHIMNEY_TALL_BBOX_HEIGHT 48

#define CHIMNEY_SHORT_BBOX_WIDTH 30
#define CHIMNEY_SHORT_BBOX_HEIGHT 32

class CChimney : public CGameObject {
protected:
	int typeChimney;
public:
	CChimney(float x, float y, int type) : CGameObject(x, y) {
		this->typeChimney = type;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
};