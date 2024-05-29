#include "EnemyManager.h"
#include "PlayScene.h"
#include "Goomba.h"

void CEnemyManager::Render()
{
	spawn3Goomba->Render();
}
void CEnemyManager::GetBoundingBox(float& l, float& t, float& r, float& b) 
{

}

void CEnemyManager::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	spawn3Goomba->Update(dt, coObjects);
	SpawnEnemy();
}

void CEnemyManager::SpawnEnemy()
{
	if (spawn3Goomba->GetIsDetectedMario() && isSpawn3Goomba == false)
	{
		isSpawn3Goomba = true;
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		LPGAMEOBJECT goomba1 = new CGoomba(850, 128);
		p->AddGameObject(goomba1);
		LPGAMEOBJECT goomba2 = new CGoomba(950, 128);
		p->AddGameObject(goomba2);
		LPGAMEOBJECT goomba3 = new CGoomba(1050, 128);
		p->AddGameObject(goomba3);
	}
}
