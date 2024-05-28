#include "Bullet.h"
#include <cmath>

#define M_PI 3.14159265358979323846

void CBullet::Render() {
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BULLET)->Render(x, y);
}

void CBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BULLET_BBOX_WIDTH / 2 + 1;
	t = y - BULLET_BBOX_HEIGHT / 2;
	r = l + BULLET_BBOX_WIDTH - 1;
	b = t + BULLET_BBOX_HEIGHT;
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBullet::SetUpAngle(float posX, float posY)
{
	float deltaX = posX - x;
	float deltaY = -(posY - y);
	float angle = atan2(deltaY, deltaX) * 180.0f / M_PI;
	float angleFire;

	if (angle >= -90 && angle <= -45) // 1
	{
		angleFire = -45;
	}
	else if (angle > -45 && angle <= 0) // 2
	{
		angleFire = -15;
	}
	else if (angle > 0 && angle <= 45) //3
	{
		angleFire = 15;
	}
	else if (angle > 45 && angle <= 90) //4
	{
		angleFire = 45;
	}
	else if (angle > 90 && angle <= 135) //5
	{
		angleFire = 135;
	}
	else if (angle > 135 && angle <= 180) //6
	{
		angleFire = 165;
	}
	else if (angle > -180 && angle <= -135) //7
	{
		angleFire = -165;
	}
	else // 8
	{
		angleFire = -135;
	}

	vx = 0.3 * cos(angleFire * M_PI / 180.0f);
	vy = -0.3 * sin(angleFire * M_PI / 180.0f);
}