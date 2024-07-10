#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Brick.h"
#include "PlayScene.h"


class CBrickManager : public CGameObject {
protected:
	vector<LPGAMEOBJECT> objects;
	static CBrickManager* __instance;
public:
	static CBrickManager* GetInstance();
	CBrickManager(float x = 0, float y = 0) : CGameObject(x, y)
	{
		Init();
	}
	void Init();
	void Render() {}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	int IsBlocking() { return 0; }
	void HandleClickedButtonP();
};

