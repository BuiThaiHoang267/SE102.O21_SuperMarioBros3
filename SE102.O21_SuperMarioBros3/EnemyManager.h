#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "OnTriggerSpawnEnemy.h"
#include "PlayScene.h"
#include "Turtle.h"

class CEnemyManager : public CGameObject {
protected:
	LPGAMEOBJECT spawn3Goomba;
	LPGAMEOBJECT spawnTurtleLeft;
	LPGAMEOBJECT spawnTurtleRight;
	LPGAMEOBJECT spawnTurtleGreenLeft;
	LPGAMEOBJECT spawnTurtleGreenRight;
	LPGAMEOBJECT spawnTurtleBrickLeft;
	LPGAMEOBJECT spawnTurtleBrickRight;

	LPGAMEOBJECT turtle;
	LPGAMEOBJECT turtle1;
	LPGAMEOBJECT turtle2;
	LPGAMEOBJECT turtle3;
	LPGAMEOBJECT turtle4;
	LPGAMEOBJECT turtleBrick;

	bool isSpawn3Goomba;
public:
	CEnemyManager(float x, float y) : CGameObject(x, y) 
	{
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);

		spawn3Goomba = new COnTriggerSpawnEnemy(711, 80, 16, 600);
		spawnTurtleLeft = new COnTriggerSpawnEnemy(424, 80, 16, 600);
		spawnTurtleRight = new COnTriggerSpawnEnemy(711, 80, 16, 600);
		spawnTurtleGreenLeft = new COnTriggerSpawnEnemy(1140, 80, 16, 600);
		spawnTurtleGreenRight = new COnTriggerSpawnEnemy(1630, 80, 16, 600);
		spawnTurtleBrickLeft = new COnTriggerSpawnEnemy(1924, 80, 16, 600);
		spawnTurtleBrickRight = new COnTriggerSpawnEnemy(2264, 80, 16, 600);

		turtle = NULL;
		turtle1 = turtle2 = turtle3 = turtle4 = NULL;
		turtleBrick = NULL;

		p->AddGameObject(spawn3Goomba);
		p->AddGameObject(spawnTurtleLeft);
		p->AddGameObject(spawnTurtleRight);
		p->AddGameObject(spawnTurtleGreenLeft);
		p->AddGameObject(spawnTurtleGreenRight);
		p->AddGameObject(spawnTurtleBrickLeft);
		p->AddGameObject(spawnTurtleBrickRight);

		isSpawn3Goomba = false;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void SpawnEnemy();
	void SpawnTurtle();
	void SpawnTurtleGreen();
	void SpawnTurtleBrick();
};