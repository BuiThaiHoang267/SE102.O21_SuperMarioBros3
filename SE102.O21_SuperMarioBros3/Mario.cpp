#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "Mushroom.h"
#include "GiftBox.h"
#include "Bullet.h"
#include "FlowerEnemy.h"
#include "Turtle.h"
#include "GoombaJump.h"
#include "Leaf.h"
#include "EffectPoint.h"
#include "Brick.h"
#include "ButtonP.h"
#include "Block.h"
#include "GiftBoxSpecial.h"
#include "PlayScene.h"
#include "CheckRangeAttackMario.h"
#include "AreaSpecial.h"
#include "UIManager.h"
#include "BlockDie.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (state == MARIO_STATE_DIE && GetTickCount64() - timer_die > 1500)
	{
		CGame::GetInstance()->InitiateSwitchScene(2);
	}
	// State Special
	if (state == MARIO_STATE_WIN)
	{
		vx = 0.06f;
		x += vx;
		maxVx = 0.2f;
		if (GetTickCount64() - timer_wined > 3000)
		{
			CGame::GetInstance()->InitiateSwitchScene(2);
		}
	}
	if (canTele)
	{
		y += vy * dt;
		if (GetTickCount64() - timer_tele > MARIO_TELE_TIME)
		{
			canTele = false;
			if (vy > 0) // tele sence hidden
			{
				x = POS_X_TETE_MAP_HIDDEN;
				y = POS_Y_TETE_MAP_HIDDEN;
				ay = MARIO_GRAVITY;
				vy = 0;
				vx = 0;
				inMapHidden = true;
				inAreaSpecial = false;
			}
			else
			{
				x = POS_X_TETE_MAP_MAIN;
				y = POS_Y_TETE_MAP_MAIN;
				ay = MARIO_GRAVITY;
				vy = 0;
				vx = 0;
				inMapHidden = false;
				inAreaSpecial = false;
			}
		}
		return;
	}

	if (state == MARIO_STATE_IDLE_MAP)
	{
		x += vx * dt;
		y += vy * dt;
		if (canDash && GetTickCount64() - timer_dash > 700)
		{
			canDash = false;
			vx = 0;
			vy = 0;
			ax = 0;
			ay = 0;
			DebugOut(L"het move");
		}
		return;
	}
	//Normal
	vx += ax * dt;
	if (isGravity)
	{
		vy += ay * dt;
	}
	if (isGravity == false && GetTickCount64() - timer_not_gravity > 200)
	{
		isGravity = true;
	}

	if ( abs(vx) > abs(maxVx) && ( (flexDirection>0 && vx > 0) || (flexDirection < 0 && vx < 0) ) ) vx = maxVx;

	if (vy > 0.3f) vy = 0.24f;

	if (state == MARIO_STATE_IDLE) 
	{
		if (vx <= 0 && ax == -MARIO_ACCEL_FRICTION_FORCE)
		{
			vx = 0.0f;
			ax = 0.0f;
		}
		else if (vx >= 0 && ax == MARIO_ACCEL_FRICTION_FORCE)
		{
			vx = 0.0f;
			ax = 0.0f;
		}
	}
	//Update pos attack zone
	if (checkAttack != NULL)
	{
		
		if (GetTickCount64() - timer_waving <= 250)
		{
			if (GetTickCount64() - timer_waving >= 125 || GetTickCount64() - timer_waving <= 175)
			{
				dynamic_cast<CCheckRangeAttackMario*>(checkAttack)->SetCanAttack(true);
			}
		}
		if (GetTickCount64() - timer_waving >= 175)
		{
			dynamic_cast<CCheckRangeAttackMario*>(checkAttack)->SetCanAttack(false);
		}
	}
	//

	CheckFly();
	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (GetTickCount64() - untouchableTurtle_start > 300)
	{
		untouchableTurtle_start = 0;
		untouchableTurtle = 0;
	}
	if (CUIManager::GetInstance()->timer <= 1 && state != MARIO_STATE_DIE)
	{
		SetState(MARIO_STATE_DIE);
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}
	
	if (!e->obj->IsCollidable()) return;

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CGiftBox*>(e->obj))
		OnCollisionWithGiftBox(e);
	else if (dynamic_cast<CGiftBoxSpecial*>(e->obj))
		OnCollisionWithGiftBoxSpecial(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CBullet*>(e->obj))
		OnCollisionWithBullet(e);
	else if (dynamic_cast<CFlowerEnemy*>(e->obj))
		OnCollisionWithFlowerEnemy(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CButtonP*>(e->obj))
		OnCollisionWithButtonP(e);
	else if (dynamic_cast<CBlockDie*>(e->obj))
		SetState(MARIO_STATE_DIE);
	else if (dynamic_cast<CTurtle*>(e->obj))
	{
		if (untouchableTurtle == 0)
		{
			OnCollisionWithTurtle(e);
			StartUntouchableTurtle();
		}
	}
	else if (dynamic_cast<CGoombaJump*>(e->obj))
	{
		OnCollisionWithGoombaJump(e);
	}
	else if (dynamic_cast<CLeaf*>(e->obj))
	{
		OnCollisionWithLeaf(e);
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			float mx, my;
			goomba->GetPosition(mx, my);
			LPGAMEOBJECT effectCoinBox = new CEffectPoint(mx, my - 16, 100);
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
			p->AddGameObject(effectCoinBox);
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level--;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}
void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	dynamic_cast<CLeaf*>(e->obj)->OnCollisionWithMario();
	SetLevel(MARIO_LEVEL_MAX);
}

void CMario::OnCollisionWithBullet(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	if (level > MARIO_LEVEL_SMALL)
	{
		level--;
		StartUntouchable();
	}
	else
	{
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
	}
}

void CMario::OnCollisionWithFlowerEnemy(LPCOLLISIONEVENT e)
{
	if (untouchable == 0)
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			level--;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithGoombaJump(LPCOLLISIONEVENT e)
{
	CGoombaJump* gbJump = dynamic_cast<CGoombaJump*>(e->obj);

	if (e->ny < 0)
	{
		int gbjLevel = gbJump->GetLevel();
		if (gbjLevel == GOOMBAJUMP_LEVEL_WING)
		{
			float mx, my;
			gbJump->GetPosition(mx, my);
			LPGAMEOBJECT effectCoinBox = new CEffectPoint(mx, my - 16, 100);
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
			p->AddGameObject(effectCoinBox);
			gbJump->SetLevel(GOOMBAJUMP_LEVEL_NORMAL);
			gbJump->SetState(GOOMBAJUMP_STATE_WALKING);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else
		{
			if (gbJump->GetState() != GOOMBAJUMP_STATE_DIE)
			{
				float mx, my;
				gbJump->GetPosition(mx, my);
				LPGAMEOBJECT effectCoinBox = new CEffectPoint(mx, my - 16, 100);
				LPSCENE s = CGame::GetInstance()->GetCurrentScene();
				LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
				p->AddGameObject(effectCoinBox);
				gbJump->SetState(GOOMBAJUMP_STATE_DIE);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		
	}
	else 
	{
		if (untouchable == 0)
		{
			if (gbJump->GetState() != GOOMBAJUMP_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level--;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithTurtle(LPCOLLISIONEVENT e)
{
	CTurtle* turtle = dynamic_cast<CTurtle*>(e->obj);

	if (turtle->GetState() == TURTLE_STATE_WALK || turtle->GetState() == TURTLE_STATE_RUN || turtle->GetState() == TURTLE_STATE_JUMP)
	{
		if (e->ny < 0)
		{
			if (turtle->GetState() != TURTLE_STATE_TORTOISESHELL)
			{
				if (turtle->GetState() == TURTLE_STATE_JUMP)
				{
					turtle->SetState(TURTLE_STATE_WALK);
				}
				else
				{
					turtle->SetState(TURTLE_STATE_TORTOISESHELL);
				}
				float mx, my;
				turtle->GetPosition(mx, my);
				LPGAMEOBJECT effectCoinBox = new CEffectPoint(mx, my - 16, 100);
				LPSCENE s = CGame::GetInstance()->GetCurrentScene();
				LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
				p->AddGameObject(effectCoinBox);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		else 
		{
			if (untouchable == 0)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level--;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
	else if ((turtle->GetState() == TURTLE_STATE_TORTOISESHELL || turtle->GetState() == TURTLE_STATE_WAKEUP) && !isPressA)
	{
		
		if (turtle->GetState() != TURTLE_STATE_RUN)
		{
			if (e->ny < 0)
			{
				float mx, my;
				turtle->GetPosition(mx, my);
				LPGAMEOBJECT effectCoinBox = new CEffectPoint(mx, my - 16, 100);
				LPSCENE s = CGame::GetInstance()->GetCurrentScene();
				LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
				p->AddGameObject(effectCoinBox);
			}
			turtle->SetState(TURTLE_STATE_RUN);
			float tx, ty;
			turtle->GetPosition(tx, ty);
			turtle->SetDirectionRun(flexDirection);
			SetState(MARIO_STATE_SHOOT_TORTOISESHELL);
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
	CUIManager::GetInstance()->coins += 1;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	DebugOut(L">>> CHUYEN SENCE >>> \n");
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithGiftBox(LPCOLLISIONEVENT e) {
	CGiftBox* m = (CGiftBox*)e->obj;
	if (e->ny > 0) {
		m->CanOpen();
	}
}

void CMario::OnCollisionWithGiftBoxSpecial(LPCOLLISIONEVENT e) {
	CGiftBoxSpecial* m = dynamic_cast<CGiftBoxSpecial*>(e->obj);
	if (e->ny > 0) {
		m->OpenGiftBox();
		this->SetState(MARIO_STATE_WIN);
	}
}


void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* b = dynamic_cast<CBrick*>(e->obj);
	if (e->ny > 0) {
		b->CanOpen(level);
	}
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e) {
	CMushroom* m = dynamic_cast<CMushroom*>(e->obj);
	m->OnCollisionWithMario(x,y - 16);
	if (m->GetTypeMushroom() == 0)
	{
		SetLevel(MARIO_LEVEL_BIG);
	}
}

void CMario::OnCollisionWithButtonP(LPCOLLISIONEVENT e)
{
	CButtonP* b = dynamic_cast<CButtonP*>(e->obj);
	if (e->ny < 0)
	{
		b->HandleClick();
	}
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	if (state == MARIO_STATE_WIN)
	{
		return ID_ANI_MARIO_SMALL_WALKING_RIGHT;
	}
	if (state == MARIO_STATE_IDLE_MAP)
	{
		return 1991;
	}
	if (GetTickCount64() - timer_shoot <= 150)
	{
		if (flexDirection == 1)
			return ID_ANI_MARIO_SMALL_SHOOT_TORTOISESHELL_RIGHT;
		else
			return ID_ANI_MARIO_SMALL_SHOOT_TORTOISESHELL_LEFT;
	}
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (isHoldTortoiseshell)
		{
			if (nx >= 0)
				return ID_ANI_MARIO_SMALL_JUMP_TORTOISESHELL_RIGHT;
			else
				return ID_ANI_MARIO_SMALL_JUMP_TORTOISESHELL_LEFT;
		}
		// Not hold tortoiseshell
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else if (isSitting)
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_BIG_SIT_RIGHT;
		else
			aniId = ID_ANI_MARIO_BIG_SIT_LEFT;
	}
	else if (vx == 0)
	{
		if (isHoldTortoiseshell)
		{
			if (nx > 0)
				return ID_ANI_MARIO_SMALL_IDLE_TORTOISESHELL_RIGHT;
			else
				return ID_ANI_MARIO_SMALL_IDLE_TORTOISESHELL_LEFT;
		}
		//not hold tortoiseshell
		if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
		else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
	}
	else if (vx > 0)
	{
		if (isHoldTortoiseshell)
		{
			if (ax == MARIO_ACCEL_RUN_X)
				return ID_ANI_MARIO_SMALL_RUN_TORTOISESHELL_RIGHT;
			else if (ax == MARIO_ACCEL_WALK_X)
				return ID_ANI_MARIO_SMALL_WALK_TORTOISESHELL_RIGHT;
			else if (ax < 0 && flexDirection == -1)
				return ID_ANI_MARIO_SMALL_WALK_TORTOISESHELL_LEFT;
			else
				return	ID_ANI_MARIO_SMALL_WALK_TORTOISESHELL_RIGHT;
		}
		//not hold tortoiseshell
		if (ax < 0 && flexDirection == -1)
			aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
		else if (ax == MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
		else if (ax == MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
		else
			aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
	}
	else // vx < 0
	{
		if (isHoldTortoiseshell)
		{
			if (ax == -MARIO_ACCEL_RUN_X)
				return ID_ANI_MARIO_SMALL_RUN_TORTOISESHELL_LEFT;
			else if (ax == -MARIO_ACCEL_WALK_X)
				return ID_ANI_MARIO_SMALL_WALK_TORTOISESHELL_LEFT;
			else if (ax > 0 && flexDirection == 1)
				return ID_ANI_MARIO_SMALL_WALK_TORTOISESHELL_RIGHT;
			else
				return	ID_ANI_MARIO_SMALL_WALK_TORTOISESHELL_LEFT;
		}
		//not hold tortoiseshell
		if (ax > 0 && flexDirection == 1)
			aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
		else if (ax == -MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
		else if (ax == -MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
		else
			aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	if (state == MARIO_STATE_WIN)
	{
		return ID_ANI_MARIO_BIG_WALKING_RIGHT;
	}
	if (GetTickCount64() - timer_shoot <= 150)
	{
		if (flexDirection == 1)
			return ID_ANI_MARIO_BIG_SHOOT_TORTOISESHELL_RIGHT;
		else
			return ID_ANI_MARIO_BIG_SHOOT_TORTOISESHELL_LEFT;
	}

	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (isHoldTortoiseshell)
			{
				if (nx >= 0)
					return ID_ANI_MARIO_BIG_JUMP_TORTOISESHELL_RIGHT;
				else
					return ID_ANI_MARIO_BIG_JUMP_TORTOISESHELL_LEFT;
			}
			// Not hold tortoiseshell
			if (nx >= 0)
				aniId = ID_ANI_MARIO_BIG_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_BIG_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
			{
				if (vy <= 0)
					aniId = ID_ANI_MARIO_BIG_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_BIG_FALL_WALK_RIGHT;
			}
			else
			{
				if(vy <= 0)
					aniId = ID_ANI_MARIO_BIG_JUMP_WALK_LEFT;
				else
					aniId = ID_ANI_MARIO_BIG_FALL_WALK_LEFT;
			}
		}
	}
	else if (isSitting)
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_BIG_SIT_RIGHT;
		else
			aniId = ID_ANI_MARIO_BIG_SIT_LEFT;
	}
	else if (vx == 0)
	{
		if (isHoldTortoiseshell)
		{
			if (nx > 0)
				return ID_ANI_MARIO_BIG_IDLE_TORTOISESHELL_RIGHT;
			else
				return ID_ANI_MARIO_BIG_IDLE_TORTOISESHELL_LEFT;
		}
		//not hold tortoiseshell
		if (nx > 0) aniId = ID_ANI_MARIO_BIG_IDLE_RIGHT;
		else aniId = ID_ANI_MARIO_BIG_IDLE_LEFT;
	}
	else if (vx > 0)
	{
		if (isHoldTortoiseshell)
		{
			if (vx >= MARIO_RUNNING_SPEED)
				return ID_ANI_MARIO_BIG_RUN_TORTOISESHELL_RIGHT;
			else if (ax == MARIO_ACCEL_WALK_X)
				return ID_ANI_MARIO_BIG_WALK_TORTOISESHELL_RIGHT;
			else if (ax < 0 && flexDirection == -1)
				return ID_ANI_MARIO_BIG_WALK_TORTOISESHELL_LEFT;
			else
				return	ID_ANI_MARIO_BIG_WALK_TORTOISESHELL_RIGHT;
		}
		//not hold tortoiseshell
		if (ax < 0 && flexDirection == -1)
			aniId = ID_ANI_MARIO_BIG_BRACE_RIGHT;
		else if (vx >= MARIO_RUNNING_SPEED)
			aniId = ID_ANI_MARIO_BIG_RUNNING_RIGHT;
		else if (ax == MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_BIG_WALKING_RIGHT;
		else
			aniId = ID_ANI_MARIO_BIG_WALKING_RIGHT;
	}
	else // vx < 0
	{
		if (isHoldTortoiseshell)
		{
			if (ax == -MARIO_ACCEL_RUN_X)
				return ID_ANI_MARIO_BIG_RUN_TORTOISESHELL_LEFT;
			else if (ax == -MARIO_ACCEL_WALK_X)
				return ID_ANI_MARIO_BIG_WALK_TORTOISESHELL_LEFT;
			else if (ax > 0 && flexDirection == 1)
				return ID_ANI_MARIO_BIG_WALK_TORTOISESHELL_RIGHT;
			else
				return ID_ANI_MARIO_BIG_WALK_TORTOISESHELL_LEFT;
		}
		//not hold tortoiseshell
		if (ax > 0 && flexDirection == 1)
			aniId = ID_ANI_MARIO_BIG_BRACE_LEFT;
		else if (ax == -MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_MARIO_BIG_RUNNING_LEFT;
		else if (ax == -MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_BIG_WALKING_LEFT;
		else
			aniId = ID_ANI_MARIO_BIG_WALKING_LEFT;
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_BIG_IDLE_RIGHT;

	return aniId;
}


int CMario::GetAniIdMax()
{
	if (state == MARIO_STATE_WIN)
	{
		return ID_ANI_MARIO_MAX_WALKING_RIGHT;
	}
	if (canTele)
	{
		return 1903;
	}

	if(GetTickCount64() - timer_waving <= 250)
	{
		if (flexDirection == 1)
			return ID_ANI_MARIO_WAVING_RIGHT;
		else
			return ID_ANI_MARIO_WAVING_LEFT;
	}

	if (GetTickCount64() - timer_shoot <= 150)
	{
		if (flexDirection == 1)
			return ID_ANI_MARIO_MAX_SHOOT_TORTOISESHELL_RIGHT;
		else
			return ID_ANI_MARIO_MAX_SHOOT_TORTOISESHELL_LEFT;
	}

	if (GetTickCount64() - timer_animation_fly <= 150)
	{
		if (flexDirection == 1 && vy <= 0)
			return ID_ANI_MARIO_MAX_FLY_RIGHT;
		else if (flexDirection == -1 && vy <= 0)
			return ID_ANI_MARIO_MAX_FLY_LEFT;
		else if (flexDirection == 1 && vy > 0)
			return ID_ANI_MARIO_MAX_FLY_FALL_RIGHT;
		else
			return ID_ANI_MARIO_MAX_FLY_FALL_LEFT;
	}
	if (isFlying && !isOnPlatform) {
		if (flexDirection == 1 && vy <= 0)
			return ID_ANI_MARIO_MAX_JUMP_RUN_RIGHT;
		else if (flexDirection == -1 && vy <= 0)
			return ID_ANI_MARIO_MAX_JUMP_RUN_LEFT;
		else if (flexDirection == 1 && vy > 0)
			return ID_ANI_MARIO_MAX_FALL_RUN_RIGHT;
		else
			return ID_ANI_MARIO_MAX_FALL_RUN_LEFT;
	}

	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(vx) >= MARIO_RUNNING_SPEED)
		{
			if (isHoldTortoiseshell)
			{
				if (nx >= 0)
					return ID_ANI_MARIO_MAX_JUMP_TORTOISESHELL_RIGHT;
				else
					return ID_ANI_MARIO_MAX_JUMP_TORTOISESHELL_LEFT;
			}
			// Not hold tortoiseshell
			if (nx >= 0)
			{
				if (vy <= 0)
					aniId = ID_ANI_MARIO_MAX_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_MAX_FALL_RUN_RIGHT;
			}
			else
			{
				if (vy <= 0)
					aniId = ID_ANI_MARIO_MAX_JUMP_RUN_LEFT;
				else
					aniId = ID_ANI_MARIO_MAX_FALL_RUN_LEFT;
			}
		}
		else
		{
			if (nx >= 0)
			{
				if (vy <= 0)
					aniId = ID_ANI_MARIO_MAX_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_MAX_FALL_WALK_RIGHT;
			}
			else
			{
				if (vy <= 0)
					aniId = ID_ANI_MARIO_MAX_JUMP_WALK_LEFT;
				else
					aniId = ID_ANI_MARIO_MAX_FALL_WALK_LEFT;
			}
		}
	}
	else if (isSitting)
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_MAX_SIT_RIGHT;
		else
			aniId = ID_ANI_MARIO_MAX_SIT_LEFT;
	}
	else if (vx == 0)
	{
		if (isHoldTortoiseshell)
		{
			if (nx > 0)
				return ID_ANI_MARIO_MAX_IDLE_TORTOISESHELL_RIGHT;
			else
				return ID_ANI_MARIO_MAX_IDLE_TORTOISESHELL_LEFT;
		}
		//not hold tortoiseshell
		if (nx > 0) aniId = ID_ANI_MARIO_MAX_IDLE_RIGHT;
		else aniId = ID_ANI_MARIO_MAX_IDLE_LEFT;
	}
	else if (vx > 0)
	{
		if (isHoldTortoiseshell)
		{
			if (vx >= MARIO_RUNNING_SPEED)
				return ID_ANI_MARIO_MAX_RUN_TORTOISESHELL_RIGHT;
			else if (ax == MARIO_ACCEL_WALK_X)
				return ID_ANI_MARIO_MAX_WALK_TORTOISESHELL_RIGHT;
			else if (ax < 0 && flexDirection == -1)
				return ID_ANI_MARIO_MAX_WALK_TORTOISESHELL_LEFT;
			else
				return	ID_ANI_MARIO_MAX_WALK_TORTOISESHELL_RIGHT;
		}
		//not hold tortoiseshell
		if (ax < 0 && flexDirection == -1)
			aniId = ID_ANI_MARIO_MAX_BRACE_RIGHT;
		else if (vx >= MARIO_RUNNING_SPEED && canFly == false)
			aniId = ID_ANI_MARIO_MAX_PRERUN_RIGHT;
		else if (vx >= MARIO_RUNNING_SPEED && canFly == true)
			aniId = ID_ANI_MARIO_MAX_RUNNING_RIGHT;
		else if (ax == MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_MAX_WALKING_RIGHT;
		else
			aniId = ID_ANI_MARIO_MAX_WALKING_RIGHT;
	}
	else // vx < 0
	{
		if (isHoldTortoiseshell)
		{
			if (vx <= -MARIO_RUNNING_SPEED)
				return ID_ANI_MARIO_MAX_RUN_TORTOISESHELL_LEFT;
			else if (ax == -MARIO_ACCEL_WALK_X)
				return ID_ANI_MARIO_MAX_WALK_TORTOISESHELL_LEFT;
			else if (ax > 0 && flexDirection == 1)
				return ID_ANI_MARIO_MAX_WALK_TORTOISESHELL_RIGHT;
			else
				return ID_ANI_MARIO_MAX_WALK_TORTOISESHELL_LEFT;
		}
		//not hold tortoiseshell
		if (ax > 0 && flexDirection == 1)
			aniId = ID_ANI_MARIO_MAX_BRACE_LEFT;
		else if (vx <= -MARIO_RUNNING_SPEED && canFly == false)
			aniId = ID_ANI_MARIO_MAX_PRERUN_LEFT;
		else if (vx <= -MARIO_RUNNING_SPEED && canFly == true)
			aniId = ID_ANI_MARIO_MAX_RUNNING_LEFT;
		else if (ax == -MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_MAX_WALKING_LEFT;
		else
			aniId = ID_ANI_MARIO_MAX_WALKING_LEFT;
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_MAX_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	//RenderBoundingBox();
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_MAX)
	{
		aniId = GetAniIdMax();
		if (flexDirection == 1)
			animations->Get(aniId)->Render(x - 3, y);
		else
			animations->Get(aniId)->Render(x + 3, y);
		return;
	}

	animations->Get(aniId)->Render(x, y);

	
	
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		flexDirection = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		flexDirection = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		flexDirection = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		flexDirection = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isFlying == true)
		{
			isOnPlatform = false;
			vy = -0.2f;
			timer_animation_fly = GetTickCount64();
			timer_not_gravity = GetTickCount64();
			isGravity = false;
		}
		if (isFlying == false && level == MARIO_LEVEL_MAX && !isOnPlatform)
		{
			timer_animation_fly = GetTickCount64();
			vy = 0.05f;
			if (abs(vx) > MARIO_WALKING_SPEED && vx * ax >= 0)
			{
				vx = flexDirection * MARIO_WALKING_SPEED;
			}
			timer_not_gravity = GetTickCount64();
			isGravity = false;
		}
		if (isOnPlatform && !isFlying)
		{
			isOnPlatform = false;
			//ax = 0.0f;
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;

			if (canFly == true && level == MARIO_LEVEL_MAX) {
				isFlying = true;
				timer_fly = GetTickCount64();
				isCamFollowMario = true;
			}
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += abs(vy)*0.5f;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		if (isOnPlatform && vx != 0) ax = MARIO_ACCEL_FRICTION_FORCE * (-flexDirection);
		else ax = 0.0f;
		break;

	case MARIO_STATE_DIE:
		CUIManager::GetInstance()->lifes--;
		timer_die = GetTickCount64();
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;

	case MARIO_STATE_SHOOT_TORTOISESHELL:
		timer_shoot = GetTickCount64();
		break;

	case MARIO_STATE_IDLE_MAP:
		ax = 0;
		ay = 0;
		break;
	case MARIO_STATE_WIN:
		timer_wined = GetTickCount64();
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG || level == MARIO_LEVEL_MAX)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

void CMario::OnTriggerEnter(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CTurtle*>(e->obj)) 
	{

		DebugOut(L"[INFO] enter trigger turtle %d\n", 1);
		CTurtle* turtle = dynamic_cast<CTurtle*>(e->obj);
		if (turtle->GetState() == TURTLE_STATE_TORTOISESHELL || turtle->GetState() == TURTLE_STATE_WAKEUP)
		{
			if (isPressA) {
				DebugOut(L"[INFO] be turtle %d\n", 1);
				this->isHoldTortoiseshell = true;
				turtle->SetState(TURTLE_STATE_MARIO_HOLD);
			}
		}
		
	}
	if (dynamic_cast<CAreaSpecial*>(e->obj))
	{
		inAreaSpecial = true;
		DebugOut(L"inAreaSpecial true\n");
	}
}
void CMario::OnTriggerStay(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CAreaSpecial*>(e->obj))
	{
		inAreaSpecial = true;
	}
	if (dynamic_cast<CTurtle*>(e->obj))
	{
		CTurtle* turtle = dynamic_cast<CTurtle*>(e->obj);
		if (turtle->GetState() == TURTLE_STATE_TORTOISESHELL || turtle->GetState() == TURTLE_STATE_WAKEUP || turtle->GetState() == TURTLE_STATE_MARIO_HOLD)
		{
			this->isHoldTortoiseshell = true;
			if (isPressA) {
				float posY;
				if (level == MARIO_LEVEL_SMALL)
					posY = y - 2;
				else
					posY = y + 2;

				if (flexDirection == 1)
					turtle->SetPosition(x + 10 , posY);
				else if (flexDirection == -1)
					turtle->SetPosition(x - 10 , posY);
			}
			else
			{
				this->isHoldTortoiseshell = false;
				SetState(MARIO_STATE_SHOOT_TORTOISESHELL);
				if (untouchableTurtle == 0)
				{
					if (turtle->GetState() != TURTLE_STATE_RUN)
					{
						turtle->SetState(TURTLE_STATE_RUN);
						turtle->SetDirectionRun(flexDirection);

						StartUntouchableTurtle();
					}
				}
			}
		}
	}
}
void CMario::OnTriggerExit(LPGAMEOBJECT e)
{
	if (dynamic_cast<CTurtle*>(e))
	{
		isHoldTortoiseshell = false;
	}
	if (dynamic_cast<CAreaSpecial*>(e))
	{
		inAreaSpecial = false;
		DebugOut(L"inAreaSpecial false\n");
	}
}

void CMario::CheckFly()
{
	if (abs(vx) >= MARIO_RUNNING_SPEED && isRunning == false)
	{
		isRunning = true;
		DebugOut(L"Pre run start\n");
		timer_pre_canFly = GetTickCount64();
	}
	if (abs(vx) < MARIO_RUNNING_SPEED && isRunning == true)
	{
		isRunning = false;
		canFly = false;
	}

	if (GetTickCount64() - timer_pre_canFly > 500 && isRunning == true && canFly == false)
	{
		DebugOut(L"Can fly start\n");
		canFly = true;
	}

	if (GetTickCount64() - timer_fly > 5000 && isFlying == true)
	{
		isFlying = false;
	}
}

void CMario::SetIsPressA(bool press)
{
	this->isPressA = press;
	if (press == true)
	{
		DebugOut(L"Key Down A\n");
	}
	else
	{
		DebugOut(L"Key Up A\n");
	}
}

void CMario::WavingTail()
{
	if (level == MARIO_LEVEL_MAX)
	{
		timer_waving = GetTickCount64();
		if (checkAttack == NULL)
		{
			checkAttack = new CCheckRangeAttackMario(x + (flexDirection * 12), y + 6, 8, 6);
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
			p->AddGameObject(checkAttack);
		}
		else
		{
			checkAttack->SetPosition(x + (flexDirection * 12), y + 6);
		}
	}
}

void CMario::Teleport(int typeSence)
{
	if (inAreaSpecial)
	{
		if (typeSence == 1 && !inMapHidden) // tele sence hidden
		{
			canTele = true;
			timer_tele = GetTickCount64();
			vy = MARIO_VY_TELE;
			ay = 0;
		}
		else if (typeSence == 0 && inMapHidden)
		{
			canTele = true;
			timer_tele = GetTickCount64();
			vy = -MARIO_VY_TELE;
			ay = 0;
		}
	}
}

void CMario::CanDash(int direction)
{
	// 1 left, 2 up, 3 right, 4 down
	bool isDash = false;
	int step = 0;

	if (direction == arrow[currentStep].first || direction == arrow[currentStep].second)
	{
		isDash = true;
	}

	if (isDash && !canDash)
	{
		if (currentStep > 0) {
			if (direction == 1 && arrow[currentStep - 1].second == 3) {
				step = -1;
			}
			else if (direction == 2 && arrow[currentStep - 1].second == 4) {
				step = -1;
			}
			else if (direction == 3 && arrow[currentStep - 1].second == 1) {
				step = -1;
			}
			else if (direction == 4 && arrow[currentStep - 1].second == 2) {
				step = -1;
			}
		}

		if (currentStep < arrow.size() - 1) {
			if (direction == 1 && arrow[currentStep + 1].first == 3) {
				step = 1;
			}
			else if (direction == 2 && arrow[currentStep + 1].first == 4) {
				step = 1;
			}
			else if (direction == 3 && arrow[currentStep + 1].first == 1) {
				step = 1;
			}
			else if (direction == 4 && arrow[currentStep + 1].first == 2) {
				step = 1;
			}
		}
		DebugOut(L"can move");
		currentStep += step;
		timer_dash = GetTickCount64();
		canDash = true;
		if (direction == 1)
			vx = -0.05f;
		else if (direction == 2)
			vy = -0.05f;
		else if (direction == 3)
			vx = 0.05f;
		else if(direction == 4)
			vy = 0.05f;
	}
}