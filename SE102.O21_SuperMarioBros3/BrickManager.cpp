#include "BrickManager.h"
#include "Brick.h"

CBrickManager* CBrickManager::__instance = NULL;

void CBrickManager::HandleClickedButtonP()
{
	for (int i = 0; i < this->objects.size(); i++)
	{
		if (objects[i]->IsDeleted())
		{
			continue;
		}
		CBrick* br = dynamic_cast<CBrick*>(objects[i]);
		br->OpenCoin();
	}
}

CBrickManager* CBrickManager::GetInstance()
{
	if (__instance == NULL) __instance = new CBrickManager(0,0);
	return __instance;
}

void CBrickManager::Init()
{
	__instance = this;
	LPSCENE s = CGame::GetInstance()->GetCurrentScene();
	LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);

	LPGAMEOBJECT br = new CBrick(2038, 112, 1);
	p->AddGameObject(br);

	br = new CBrick(1958, 144, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	br = new CBrick(1974, 144, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	br = new CBrick(1990, 144, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	br = new CBrick(2006, 144, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	br = new CBrick(2022, 144, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	br = new CBrick(2038, 144, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	br = new CBrick(2054, 144, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	br = new CBrick(1974, 128, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	br = new CBrick(1990, 128, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	br = new CBrick(2006, 128, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	br = new CBrick(2022, 128, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	br = new CBrick(2038, 128, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	br = new CBrick(1990, 112, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	br = new CBrick(2006, 112, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	br = new CBrick(2022, 112, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	// 3 cuc rieng le
	br = new CBrick(2102, 144, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	br = new CBrick(2118, 144, 0);
	p->AddGameObject(br);
	objects.push_back(br);

	br = new CBrick(2102, 128, 0);
	p->AddGameObject(br);
	objects.push_back(br);
}