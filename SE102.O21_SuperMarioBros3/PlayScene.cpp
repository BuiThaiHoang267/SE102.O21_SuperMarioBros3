#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "BoxColor.h"
#include "ObjectBackground.h"
#include "GiftBox.h"
#include "Mushroom.h"
#include "Effect.h"
#include "EffectCoinBox.h"
#include "EffectPoint.h"
#include "Chimney.h"
#include "FlowerEnemy.h"
#include "Raycast.h"
#include "Bullet.h"
#include "Turtle.h"
#include "EnemyManager.h"
#include "GoombaJump.h"
#include "Leaf.h"
#include "TitleMap.h"
#include "TitleMapCloud.h"
#include "BrickManager.h"
#include "Block.h"
#include "BlockDie.h"
#include "BackGroundBlack.h"
#include "GiftBoxSpecial.h"
#include "AreaSpecial.h"
#include "PanelUI.h"

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	panel = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y); 
		player = (CMario*)obj;
		objects.push_back(obj);

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA:
		{
			obj = new CGoomba(x, y);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_BULLET:
		{
			float posX = (float)atof(tokens[3].c_str());
			float posY = (float)atof(tokens[4].c_str());
			obj = new CBullet(x, y, posX, posY);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_BLOCK:
		{
			int width = atoi(tokens[3].c_str());
			int height = atoi(tokens[4].c_str());
			obj = new CBlock(x, y, width, height);
			objects.push_back(obj);
		}
		break;	
	case OBJECT_TYPE_BLOCK_DIE:
		{
			int width = atoi(tokens[3].c_str());
			int height = atoi(tokens[4].c_str());
			obj = new CBlockDie(x, y, width, height);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_GIFTBOX: 
		{
			int type = atoi(tokens[3].c_str());
			obj = new CGiftBox(x, y, type);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_CHIMNEY:
		{
			int type = atoi(tokens[3].c_str());
			obj = new CChimney(x, y, type);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_BRICK: 
		{
			int type = atoi(tokens[3].c_str());
			obj = new CBrick(x, y, type);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_COIN: 
		{
			int isAnim = atoi(tokens[3].c_str());
			obj = new CCoin(x, y, isAnim);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_RAYCAST:
		{
			int width = atoi(tokens[3].c_str());
			int height = atoi(tokens[4].c_str());
			obj = new CRaycast(x, y, width, height);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_AREASPECIAL:
		{
			int width = atoi(tokens[3].c_str());
			int height = atoi(tokens[4].c_str());
			obj = new CAreaSpecial(x, y, width, height);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_EFFECTCOINBOX:
		{
			obj = new CEffectCoinBox(x, y);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_GIFTBOX_SPECIAL:
		{
			obj = new CGiftBoxSpecial(x, y);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_TURTLE:
		{
			int direction = atoi(tokens[3].c_str());
			int type = atoi(tokens[4].c_str());
			obj = new CTurtle(x, y, direction, type);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_BRICK_MANAGER:
		{
			obj = new CBrickManager(x, y);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_GOOMBAJUMP:
		{
			obj = new CGoombaJump(x, y);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_ENEMYMANAGER:
		{
			obj = new CEnemyManager(x, y);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_EFFECTPOINT:
		{
			int point = atoi(tokens[3].c_str());
			obj = new CEffectPoint(x, y, point);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_MUSHROOM: 
		{
			int type = atoi(tokens[3].c_str());
			obj = new CMushroom(x, y, type);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_FLOWERENEMY:
		{
			int type = atoi(tokens[3].c_str());
			obj = new CFlowerEnemy(x, y, type);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_LEAF:
		{
			obj = new CLeaf(x, y);
			objects.push_back(obj);
		}
		break;
	case OBJECT_TYPE_PLATFORM:
		{
			float cell_width = (float)atof(tokens[3].c_str());
			float cell_height = (float)atof(tokens[4].c_str());
			int length = atoi(tokens[5].c_str());
			int sprite_begin = atoi(tokens[6].c_str());
			int sprite_middle = atoi(tokens[7].c_str());
			int sprite_end = atoi(tokens[8].c_str());

			obj = new CPlatform(
				x, y,
				cell_width, cell_height, length,
				sprite_begin, sprite_middle, sprite_end
			);
			objects.push_back(obj);
		}
		break;

	case OBJECT_TYPE_TITLEMAP:
		{
			float cell_width = (float)atof(tokens[3].c_str());
			float cell_height = (float)atof(tokens[4].c_str());
			int length = atoi(tokens[5].c_str());
			int sprite_begin = atoi(tokens[6].c_str());
			int sprite_middle = atoi(tokens[7].c_str());
			int sprite_end = atoi(tokens[8].c_str());

			obj = new CTitleMap(
				x, y,
				cell_width, cell_height, length,
				sprite_begin, sprite_middle, sprite_end
			);
			objectsBgr.push_back(obj);
		}
		break;

	case OBJECT_TYPE_BGR_BLACK:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CBackGroundBlack(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);
		objectsBgr.push_back(obj);
	}
	break;

	case OBJECT_TYPE_TITLEMAP_CLOUD:
		{
			float cell_width = (float)atof(tokens[3].c_str());
			float cell_height = (float)atof(tokens[4].c_str());
			int length = atoi(tokens[5].c_str());
			int sprite_begin = atoi(tokens[6].c_str());
			int sprite_middle = atoi(tokens[7].c_str());
			int sprite_end = atoi(tokens[8].c_str());

			obj = new CTitleMapCloud(
				x, y,
				cell_width, cell_height, length,
				sprite_begin, sprite_middle, sprite_end
			);
			objects.push_back(obj);
		}
		break;

	case OBJECT_TYPE_BOXCOLOR:
		{
			int width = atoi(tokens[3].c_str());
			int height = atoi(tokens[4].c_str());
			int spriteId = atoi(tokens[5].c_str());
			int paddingRight = atoi(tokens[6].c_str());
			obj = new CBoxColor(x, y, width, height, spriteId,paddingRight);
			objectsBgr.push_back(obj);
		}
		break;

	case OBJECT_TYPE_PANEL_UI:
		{
			int width = atoi(tokens[3].c_str());
			int height = atoi(tokens[4].c_str());
			int spriteId = atoi(tokens[5].c_str());
			obj = new CPanelUI(x, y, width, height, spriteId);
			panel = (CPanelUI*)obj;
			objects.push_back(obj);
		}
		break;

	case OBJECT_TYPE_OBJECTBACKGROUND:
		{
			int width = atoi(tokens[3].c_str());
			int height = atoi(tokens[4].c_str());
			int spriteId = atoi(tokens[5].c_str());
			obj = new CObjectBackground(x, y, width, height, spriteId);
			objectsBgr.push_back(obj);
		}
		break;

	case OBJECT_TYPE_PORTAL:
		{
			float r = (float)atof(tokens[3].c_str());
			float b = (float)atof(tokens[4].c_str());
			int scene_id = atoi(tokens[5].c_str());
			obj = new CPortal(x, y, r, b, scene_id);
			objects.push_back(obj);
		}
		break;

	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	//obj->SetPosition(x, y);


	//objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	//vector<LPGAMEOBJECT> coObjectsBgr;
	
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objectsBgr.size(); i++)
	{
		coObjects.push_back(objectsBgr[i]);
	}
	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	for (size_t i = 0; i < objectsBgr.size(); i++)
	{
		objectsBgr[i]->Update(dt, &coObjects);
	}
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);
	CMario* mario = dynamic_cast<CMario*>(player);

	CGame *game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;

	if (mario->GetIsCamFollowMario())
	{
		if (cy > -24 && !mario->GetIsFlying())
			mario->SetIsCamFollowMario(false);
	}
	else
	{
		cy = -24.0f;
	}

	if (cx < 0)
		cx = 0;
	else if (cx > 2550.0f)
		cx = 2550.0f;

	if (cy > -24)
		cy = -24;
	else if (cy < -256)
		cy = -256;

	if (mario->GetInMapHidden())
	{
		cy = 216;
	}

	if (panel != NULL)
	{
		panel->SetPosition(cx +10 + 115 , cy + 216);
	}
	CGame::GetInstance()->SetCamPos(cx,cy);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	float x, y;
	float mx, my;
	player->GetPosition(x, y);

	for (int i = 0; i < objectsBgr.size(); i++)
	{
		objectsBgr[i]->GetPosition(mx, my);
		if (mx <= x - 260.0f || mx >= x + 260.0f)
		{
			if (!dynamic_cast<CBackGroundBlack*>(objectsBgr[i]))
				continue;
		}
		objectsBgr[i]->Render();
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->GetPosition(mx, my);
		if (mx <= x - 260.0f || mx >= x + 260.0f)
		{
			if(!dynamic_cast<CPlatform*>(objects[i]) && !dynamic_cast<CTitleMapCloud*>(objects[i]))
				continue;
		}
		objects[i]->Render();
	}
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator itBgr;
	for (itBgr = objectsBgr.begin(); itBgr != objectsBgr.end(); itBgr++)
	{
		delete (*itBgr);
	}
	objectsBgr.clear();

	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objectsBgr.size(); i++)
		delete objectsBgr[i];

	objectsBgr.clear();

	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;
	panel = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator itBgr;
	for (itBgr = objectsBgr.begin(); itBgr != objectsBgr.end(); itBgr++)
	{
		LPGAMEOBJECT o = *itBgr;
		if (o->IsDeleted())
		{
			delete o;
			*itBgr = NULL;
		}
	}

	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objectsBgr.erase(
		std::remove_if(objectsBgr.begin(), objectsBgr.end(), CPlayScene::IsGameObjectDeleted),
		objectsBgr.end());
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
	
}

void CPlayScene::AddGameObject(LPGAMEOBJECT obj) {
	objects.insert(objects.begin(), obj);
}

void CPlayScene::AddGameObjectPushBack(LPGAMEOBJECT obj) {
	objects.push_back(obj);
}