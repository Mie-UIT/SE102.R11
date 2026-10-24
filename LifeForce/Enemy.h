#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ENEMY_SCALE 0.18f
#define ENEMY_BBOX_WIDTH (97.0f * ENEMY_SCALE)
#define ENEMY_BBOX_HEIGHT (98.0f * ENEMY_SCALE)

#define ENEMY_STATE_IDLE 0
#define ENEMY_STATE_DIE 100

#define ID_SPRITE_ENEMY_1 30001
#define ID_SPRITE_ENEMY_2 30002
#define ID_SPRITE_ENEMY_3 30003
#define ID_SPRITE_ENEMY_4 30004
#define ID_SPRITE_ENEMY_5 30005
#define ID_SPRITE_ENEMY_6 30006
#define ID_SPRITE_ENEMY_7 30007

#define ID_ANI_ENEMY_IDLE 3000
#define ID_ANI_ENEMY_DIE 3001

class CEnemy : public CGameObject
{
	bool isDead;
public:
	CEnemy(float x, float y) : CGameObject(x, y)
	{
		this->vx = 0.0f;
		this->vy = 0.0f;
		this->state = ENEMY_STATE_IDLE;
		this->isDead = false;
	}

	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	bool IsDead() { return isDead; }
};
