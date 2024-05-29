#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "OnTriggerSpawnEnemy.h"


class CEnemyManager : public CGameObject {
protected:
	COnTriggerSpawnEnemy* spawn3Goomba;
	bool isSpawn3Goomba;
public:
	CEnemyManager(float x, float y) : CGameObject(x, y) 
	{
		spawn3Goomba = new COnTriggerSpawnEnemy(711, 80, 20, 120);
		isSpawn3Goomba = false;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void SpawnEnemy();
};