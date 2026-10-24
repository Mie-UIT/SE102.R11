#include "Bullet.h"

#define SCREEN_WIDTH 320.0f
#define SCREEN_HEIGHT 240.0f

void CBullet::Update(DWORD dt)
{
	if (!isActive) return;

	x += vx * dt;
	y += vy * dt;

	if (x > SCREEN_WIDTH || x < 0.0f || y > SCREEN_HEIGHT || y < 0.0f)
	{
		Deactivate();
	}
}

void CBullet::Render()
{
	if (!isActive) return;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BULLET)->Render(x, y, BULLET_SCALE);
}
