#include "EnemyManager.h"
#include "PlayScene.h"
#include "Goomba.h"
#include "GoombaJump.h"
#include "Turtle.h"

void CEnemyManager::Render()
{
	//RenderBoundingBox();
}
void CEnemyManager::GetBoundingBox(float& l, float& t, float& r, float& b) 
{
	t = 100 - 50;
	l = 100 - 50;
	r = l + 50;
	b = t + 50;
}

void CEnemyManager::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SpawnEnemy();
}

void CEnemyManager::SpawnEnemy()
{
	//Goomba
	if (dynamic_cast<COnTriggerSpawnEnemy*>(spawn3Goomba)->GetIsDetectedMario() && isSpawn3Goomba == false)
	{
		isSpawn3Goomba = true;
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		LPGAMEOBJECT goomba1 = new CGoomba(850, 128);
		p->AddGameObject(goomba1);
		LPGAMEOBJECT goomba2 = new CGoomba(914, 128);
		p->AddGameObject(goomba2);
		LPGAMEOBJECT goomba3 = new CGoombaJump(978, 128);
		p->AddGameObject(goomba3);
	}
	//turtle
	SpawnTurtle();
	SpawnTurtleGreen();
	SpawnTurtleBrick();
}

void CEnemyManager::SpawnTurtle()
{
	if (dynamic_cast<COnTriggerSpawnEnemy*>(spawnTurtleLeft)->GetIsDetectedMario() || dynamic_cast<COnTriggerSpawnEnemy*>(spawnTurtleRight)->GetIsDetectedMario())
	{
		if (turtle != NULL)
		{
			if (!turtle->IsDeleted())
				return;
			else
			{
				LPSCENE s = CGame::GetInstance()->GetCurrentScene();
				LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
				turtle = new CTurtle(576, 100, -1, 0);
				p->AddGameObjectPushBack(turtle);
			}
		}
		else 
		{
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
			turtle = new CTurtle(576, 100, -1, 0);
			p->AddGameObjectPushBack(turtle);
		}
	}
}
void CEnemyManager::SpawnTurtleGreen()
{
	if (
		dynamic_cast<COnTriggerSpawnEnemy*>(spawnTurtleGreenLeft)->GetIsDetectedMario() 
		|| dynamic_cast<COnTriggerSpawnEnemy*>(spawnTurtleGreenRight)->GetIsDetectedMario())
	{

		if(turtle1 == NULL || (turtle1!=NULL && turtle1->IsDeleted()))
		{
			int direction;
			if (dynamic_cast<COnTriggerSpawnEnemy*>(spawnTurtleGreenLeft)->GetIsDetectedMario())
				direction = -1;
			else
				direction = 1;
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
			turtle1 = new CTurtle(1335, 40, direction, 2);
			p->AddGameObjectPushBack(turtle1);
		}

		if (turtle2 == NULL || (turtle2 != NULL && turtle2->IsDeleted()))
		{
			int direction;
			if (dynamic_cast<COnTriggerSpawnEnemy*>(spawnTurtleGreenLeft)->GetIsDetectedMario())
				direction = -1;
			else
				direction = 1;
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
			turtle2 = new CTurtle(1384, 40, direction, 2);
			p->AddGameObjectPushBack(turtle2);
		}

		if (turtle3 == NULL || (turtle3 != NULL && turtle3->IsDeleted()))
		{
			int direction;
			if (dynamic_cast<COnTriggerSpawnEnemy*>(spawnTurtleGreenLeft)->GetIsDetectedMario())
				direction = -1;
			else
				direction = 1;
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
			turtle3 = new CTurtle(1432, 40, direction, 2);
			p->AddGameObjectPushBack(turtle3);
		}

		if (turtle4 == NULL || (turtle4 != NULL && turtle4->IsDeleted()))
		{
			int direction;
			if (dynamic_cast<COnTriggerSpawnEnemy*>(spawnTurtleGreenLeft)->GetIsDetectedMario())
				direction = -1;
			else
				direction = 1;
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
			turtle4 = new CTurtle(1456, 100, direction, 1);
			p->AddGameObjectPushBack(turtle4);
		}
	}
}
void CEnemyManager::SpawnTurtleBrick()
{
	if (dynamic_cast<COnTriggerSpawnEnemy*>(spawnTurtleBrickLeft)->GetIsDetectedMario() || dynamic_cast<COnTriggerSpawnEnemy*>(spawnTurtleBrickRight)->GetIsDetectedMario())
	{
		if (turtleBrick != NULL)
		{
			if (!turtleBrick->IsDeleted())
				return;
			else
			{
				LPSCENE s = CGame::GetInstance()->GetCurrentScene();
				LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
				turtleBrick = new CTurtle(2104, 100, -1, 0);
				p->AddGameObjectPushBack(turtleBrick);
			}
		}
		else 
		{
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
			turtleBrick = new CTurtle(2104, 100, -1, 0);
			p->AddGameObjectPushBack(turtleBrick);
		}
	}
}
