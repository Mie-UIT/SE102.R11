#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define BULLET_SPEED 0.2f
#define BULLET_SCALE 0.5f
#define BULLET_BBOX_WIDTH 12.0f
#define BULLET_BBOX_HEIGHT 8.0f

#define ID_SPRITE_BULLET_1 20001
#define ID_SPRITE_BULLET_2 20002
#define ID_SPRITE_BULLET_3 20003

#define ID_ANI_BULLET 2000

class CBullet : public CGameObject
{
	bool isActive;
public:
	CBullet(float x, float y) : CGameObject(x, y)
	{
		this->vx = BULLET_SPEED;
		this->vy = 0.0f;
		this->isActive = true;
	}

	void Update(DWORD dt);
	void Render();
	bool IsActive() { return isActive; }
	void Deactivate() { isActive = false; }
};
