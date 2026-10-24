#include "Enemy.h"


void CEnemy::Update(DWORD dt)
{
	if (isDead) return;

	x += vx * dt;
	y += vy * dt;

	if (state == ENEMY_STATE_DIE)
	{
		LPANIMATION aniDie = CAnimations::GetInstance()->Get(ID_ANI_ENEMY_DIE);
		if (aniDie != NULL && aniDie->IsFinished())
		{
			isDead = true;
		}
	}
}

void CEnemy::Render()
{
	if (isDead) return;

	CAnimations* animations = CAnimations::GetInstance();
	int aniId = (state == ENEMY_STATE_DIE) ? ID_ANI_ENEMY_DIE : ID_ANI_ENEMY_IDLE;

	LPANIMATION ani = animations->Get(aniId);
	if (ani != NULL)
	{
		ani->Render(x, y, ENEMY_SCALE);
		if (state == ENEMY_STATE_DIE && ani->IsFinished())
		{
			isDead = true;
		}
	}
}

void CEnemy::SetState(int state)
{
	if (state == ENEMY_STATE_DIE && this->state != ENEMY_STATE_DIE)
	{
		LPANIMATION aniDie = CAnimations::GetInstance()->Get(ID_ANI_ENEMY_DIE);
		if (aniDie != NULL) aniDie->Reset();
	}
	CGameObject::SetState(state);
}
