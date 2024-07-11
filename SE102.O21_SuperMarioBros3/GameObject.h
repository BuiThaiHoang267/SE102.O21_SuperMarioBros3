#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>
#include <unordered_set>

#include "Animation.h"
#include "Animations.h"
#include "Sprites.h"
#include "Collision.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define BBOX_ALPHA 0.25f		// Bounding box transparency
#define TAG_ENEMY 1
#define VX_COLLIDER_TORTOISESHELL 0.05f
#define VY_COLLIDER_TORTOISESHELL 0.26f
#define GRAVITY_COLLIDER_TORTOISESHELL 0.001f


class CGameObject
{
protected:

	float x; 
	float y;

	float vx;
	float vy;

	int nx;	 

	int state;

	bool isDeleted;

	int tag;

public: 
	std::unordered_set<LPGAMEOBJECT> prevCollidingObjects;
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	int GetTag() { return this->tag; }
	int GetState() { return this->state; }
	virtual void Delete() { isDeleted = true;  }
	bool IsDeleted() { return isDeleted; }

	void RenderBoundingBox();

	CGameObject();
	CGameObject(float x, float y) :CGameObject() { this->x = x; this->y = y; }

	virtual int IsStatic() { return 0; };

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	//
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	//
	virtual int IsCollidable() { return 0; };

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};
	
	//Trigger update
	virtual void OnTriggerEnter(LPCOLLISIONEVENT e) {};
	virtual void OnTriggerStay(LPCOLLISIONEVENT e) {};
	virtual void OnTriggerExit(LPGAMEOBJECT e) {};

	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	virtual int IsBlocking() { return 1; }

	// Is this object collide with other object at certain direction ( like ColorBox )
	virtual int IsDirectionColliable(float nx, float ny) { return 1; }

	~CGameObject();

	static bool IsDeleted(const LPGAMEOBJECT &o) { return o->isDeleted; }
};
