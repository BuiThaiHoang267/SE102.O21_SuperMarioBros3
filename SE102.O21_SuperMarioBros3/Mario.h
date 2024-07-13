#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "PlayScene.h"
#include "CheckRangeAttackMario.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.096f
#define MARIO_RUNNING_SPEED		0.204f

#define MARIO_ACCEL_FRICTION_FORCE	0.00016f
#define MARIO_ACCEL_WALK_X			0.00028f
#define MARIO_ACCEL_RUN_X			0.00036f

#define MARIO_JUMP_SPEED_Y		0.36f
#define MARIO_JUMP_RUN_SPEED_Y	0.42f

#define MARIO_GRAVITY			0.0008f

#define MARIO_JUMP_DEFLECT_SPEED  0.3f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_SHOOT_TORTOISESHELL 701

#define MARIO_STATE_WAVING 800
#define MARIO_STATE_IDLE_MAP 801
#define MARIO_STATE_WIN 802


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_BIG_IDLE_RIGHT 400
#define ID_ANI_MARIO_BIG_IDLE_LEFT 401

#define ID_ANI_MARIO_BIG_WALKING_RIGHT 500
#define ID_ANI_MARIO_BIG_WALKING_LEFT 501

#define ID_ANI_MARIO_BIG_RUNNING_RIGHT 600
#define ID_ANI_MARIO_BIG_RUNNING_LEFT 601

#define ID_ANI_MARIO_BIG_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_BIG_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_BIG_FALL_WALK_RIGHT 702
#define ID_ANI_MARIO_BIG_FALL_WALK_LEFT 703

#define ID_ANI_MARIO_BIG_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_BIG_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_BIG_SIT_RIGHT 900
#define ID_ANI_MARIO_BIG_SIT_LEFT 901

#define ID_ANI_MARIO_BIG_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BIG_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

#define ID_ANI_MARIO_BIG_IDLE_TORTOISESHELL_LEFT	1700
#define ID_ANI_MARIO_BIG_IDLE_TORTOISESHELL_RIGHT	1701

#define ID_ANI_MARIO_BIG_WALK_TORTOISESHELL_LEFT	1702
#define ID_ANI_MARIO_BIG_WALK_TORTOISESHELL_RIGHT	1703

#define ID_ANI_MARIO_BIG_RUN_TORTOISESHELL_LEFT		1704
#define ID_ANI_MARIO_BIG_RUN_TORTOISESHELL_RIGHT	1705

#define ID_ANI_MARIO_BIG_SHOOT_TORTOISESHELL_LEFT	1706
#define ID_ANI_MARIO_BIG_SHOOT_TORTOISESHELL_RIGHT	1707

#define ID_ANI_MARIO_BIG_JUMP_TORTOISESHELL_LEFT	1708
#define ID_ANI_MARIO_BIG_JUMP_TORTOISESHELL_RIGHT	1709


// MAX LEVEL MARIO
#define ID_ANI_MARIO_MAX_IDLE_RIGHT					420
#define ID_ANI_MARIO_MAX_IDLE_LEFT					421

#define ID_ANI_MARIO_MAX_WALKING_RIGHT				520
#define ID_ANI_MARIO_MAX_WALKING_LEFT				521

#define ID_ANI_MARIO_MAX_PRERUN_RIGHT				522
#define ID_ANI_MARIO_MAX_PRERUN_LEFT				523

#define ID_ANI_MARIO_MAX_RUNNING_RIGHT				620
#define ID_ANI_MARIO_MAX_RUNNING_LEFT				621

#define ID_ANI_MARIO_MAX_JUMP_WALK_RIGHT			720
#define ID_ANI_MARIO_MAX_JUMP_WALK_LEFT				721

#define ID_ANI_MARIO_MAX_FALL_WALK_RIGHT			722
#define ID_ANI_MARIO_MAX_FALL_WALK_LEFT				723

#define ID_ANI_MARIO_MAX_JUMP_RUN_RIGHT				820
#define ID_ANI_MARIO_MAX_JUMP_RUN_LEFT				821

#define ID_ANI_MARIO_MAX_FALL_RUN_RIGHT				822
#define ID_ANI_MARIO_MAX_FALL_RUN_LEFT				823

#define ID_ANI_MARIO_MAX_SIT_RIGHT					920
#define ID_ANI_MARIO_MAX_SIT_LEFT					921

#define ID_ANI_MARIO_MAX_BRACE_RIGHT				1020
#define ID_ANI_MARIO_MAX_BRACE_LEFT					1021

#define ID_ANI_MARIO_MAX_IDLE_TORTOISESHELL_LEFT	1720
#define ID_ANI_MARIO_MAX_IDLE_TORTOISESHELL_RIGHT	1721

#define ID_ANI_MARIO_MAX_WALK_TORTOISESHELL_LEFT	1722
#define ID_ANI_MARIO_MAX_WALK_TORTOISESHELL_RIGHT	1723

#define ID_ANI_MARIO_MAX_RUN_TORTOISESHELL_LEFT		1724
#define ID_ANI_MARIO_MAX_RUN_TORTOISESHELL_RIGHT	1725

#define ID_ANI_MARIO_MAX_SHOOT_TORTOISESHELL_LEFT	1726
#define ID_ANI_MARIO_MAX_SHOOT_TORTOISESHELL_RIGHT	1727

#define ID_ANI_MARIO_MAX_JUMP_TORTOISESHELL_LEFT	1728
#define ID_ANI_MARIO_MAX_JUMP_TORTOISESHELL_RIGHT	1729

#define ID_ANI_MARIO_MAX_FLY_LEFT					1820
#define ID_ANI_MARIO_MAX_FLY_RIGHT					1821

#define ID_ANI_MARIO_MAX_FLY_FALL_LEFT				1822
#define ID_ANI_MARIO_MAX_FLY_FALL_RIGHT				1823

#define ID_ANI_MARIO_WAVING_LEFT					1901
#define ID_ANI_MARIO_WAVING_RIGHT					1902

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_IDLE_TORTOISESHELL_LEFT		1710
#define ID_ANI_MARIO_SMALL_IDLE_TORTOISESHELL_RIGHT		1711

#define ID_ANI_MARIO_SMALL_WALK_TORTOISESHELL_LEFT		1712
#define ID_ANI_MARIO_SMALL_WALK_TORTOISESHELL_RIGHT		1713

#define ID_ANI_MARIO_SMALL_RUN_TORTOISESHELL_LEFT		1714
#define ID_ANI_MARIO_SMALL_RUN_TORTOISESHELL_RIGHT		1715

#define ID_ANI_MARIO_SMALL_SHOOT_TORTOISESHELL_LEFT		1716
#define ID_ANI_MARIO_SMALL_SHOOT_TORTOISESHELL_RIGHT	1717

#define ID_ANI_MARIO_SMALL_JUMP_TORTOISESHELL_LEFT		1718
#define ID_ANI_MARIO_SMALL_JUMP_TORTOISESHELL_RIGHT		1719

#pragma endregion

#define GROUND_Y 160.0f

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_MAX		3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 26
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 14

#define POS_X_TETE_MAP_HIDDEN	1807
#define POS_Y_TETE_MAP_HIDDEN	272

#define POS_X_TETE_MAP_MAIN	2336
#define POS_Y_TETE_MAP_MAIN	100	

#define MARIO_VY_TELE 0.03f;

#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_TELE_TIME 2000

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	BOOLEAN isOnPlatform;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 
	int untouchableTurtle;
	int flexDirection;
	int coin; 
	bool isPressA;
	bool isHoldTortoiseshell;
	bool canFly;
	bool isRunning;
	bool isFlying;
	bool isCamFollowMario;
	bool isGravity;
	bool canWaving;
	bool canTele;
	bool inAreaSpecial;
	bool inMapHidden;
	bool canDash;
	ULONGLONG untouchable_start;
	ULONGLONG untouchableTurtle_start;
	ULONGLONG timer_shoot;
	ULONGLONG timer_pre_canFly;
	ULONGLONG timer_fly;
	ULONGLONG timer_animation_fly;
	ULONGLONG timer_not_gravity;
	ULONGLONG timer_waving;
	ULONGLONG timer_tele;
	ULONGLONG timer_dash;
	ULONGLONG timer_wined;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithGiftBox(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithBullet(LPCOLLISIONEVENT e);
	void OnCollisionWithFlowerEnemy(LPCOLLISIONEVENT e);
	void OnCollisionWithTurtle(LPCOLLISIONEVENT e);
	void OnCollisionWithGoombaJump(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithButtonP(LPCOLLISIONEVENT e);
	void OnCollisionWithGiftBoxSpecial(LPCOLLISIONEVENT e);

	LPGAMEOBJECT checkAttack;

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdMax();

public:
	int currentStep;
	vector<std::pair<int, int>> arrow = {
		{0, 3},
		{1, 2},
		{4, 0}
	};
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		//level = MARIO_LEVEL_SMALL;
		level = 1;
		untouchable = 0;
		currentStep = 0;
		untouchableTurtle_start = -1;
		untouchable_start = -1;
		timer_shoot = -1;
		timer_pre_canFly = -1;
		timer_fly = -1;
		timer_animation_fly = -1;
		timer_not_gravity = -1;
		timer_waving = -1;
		timer_tele = -1;
		timer_dash = -1;
		timer_wined = -1;
		untouchableTurtle = 0;
		coin = 0;
		isOnPlatform = false;
		isHoldTortoiseshell = false;
		isPressA = false;
		canFly = false;
		isRunning = false;
		isFlying = false;
		isCamFollowMario = false;
		isGravity = true;
		canWaving = false;
		canTele = false;
		inAreaSpecial = false;
		inMapHidden = false;
		canDash = false;
		flexDirection = 1;

		this->checkAttack = NULL;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void SetLevel(int l);
	int GetLevel() { return this->level; };
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartUntouchableTurtle() { untouchableTurtle = 1; untouchableTurtle_start = GetTickCount64(); }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetIsPressA(bool press);
	void OnTriggerEnter(LPCOLLISIONEVENT e);
	void OnTriggerStay(LPCOLLISIONEVENT e);
	void OnTriggerExit(LPGAMEOBJECT e);
	void CheckFly();
	bool GetIsFlying() { return this->isFlying; }
	bool GetIsCamFollowMario() { return this->isCamFollowMario; }
	void SetIsCamFollowMario(bool isFollow) { this->isCamFollowMario = isFollow; }
	void WavingTail();
	void SetCanWaving(bool canWaving) { this->canWaving = canWaving; }
	void Teleport(int typeSence);
	bool GetInMapHidden() { return inMapHidden; }
	void CanDash(int direction);
};