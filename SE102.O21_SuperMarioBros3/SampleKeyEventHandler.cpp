#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_A:
		mario->SetIsPressA(true);
		mario->WavingTail();
		break;
	case DIK_DOWN:
	{
		if (mario->GetState() == MARIO_STATE_IDLE_MAP)
		{
			DebugOut(L"DOWN\n");
			mario->CanDash(4);
		}
		else
			mario->SetState(MARIO_STATE_SIT);
	}
		break;
	case DIK_UP:
		DebugOut(L"UP\n");
		mario->CanDash(2);
		break;
	case DIK_LEFT:
		DebugOut(L"LEFT\n");
		mario->CanDash(1);
		break;
	case DIK_RIGHT:
		DebugOut(L"Right\n");
		mario->CanDash(3);
		break;
	case DIK_S:
	{
		if (mario->GetState() == MARIO_STATE_IDLE_MAP)
		{
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			CPlayScene* scene = dynamic_cast<CPlayScene*>(s);
			if (mario->arrow.size()-1 == mario->currentStep)
			{
				CGame::GetInstance()->InitiateSwitchScene(3);
			}
		}
		else
			mario->SetState(MARIO_STATE_JUMP);
	}
		break;
	case DIK_W:
		{
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			CPlayScene* scene = dynamic_cast<CPlayScene*>(s);
			if (scene->GetIdScene() == 4)
			{
				CGame::GetInstance()->InitiateSwitchScene(2);
			}
		}
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_MAX);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		// Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_A:
		mario->SetIsPressA(false);
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (mario->GetState() != MARIO_STATE_IDLE_MAP)
		{
			if (game->IsKeyDown(DIK_A))
				mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			else
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (mario->GetState() != MARIO_STATE_IDLE_MAP)
		{
			if (game->IsKeyDown(DIK_A))
				mario->SetState(MARIO_STATE_RUNNING_LEFT);
			else
				mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		mario->Teleport(0);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		mario->Teleport(1);
	}
	else
	{
		mario->SetState(MARIO_STATE_IDLE);
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		CPlayScene* scene = dynamic_cast<CPlayScene*>(s);
		if (scene->GetIdScene() == 2)
		{
			mario->SetState(MARIO_STATE_IDLE_MAP);
		}
	}
}