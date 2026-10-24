#include "LifeForce.h"

void CLifeForce::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	vx += ax * dt;
	vy += ay * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;
	if (abs(vy) > abs(maxVy)) vy = maxVy;

	DebugOutTitle(L"vx = %0.5f, vy = %0.5f", this->vx, this->vy);

	// simple screen edge collision!!!
	if (vx > 0 && x > 290) x = 290;
	if (vx < 0 && x < 10) x = 10;

	if (vy > 0 && y > 200) y = 200;
	if (vy < 0 && y < 10) y = 10;
}

void CLifeForce::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_MARIO_IDLE_RIGHT;

	animations->Get(aniId)->Render(x, y);
}

void CLifeForce::SetStateX(int state)
{
	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_IDLE:
		maxVx = 0.0f;
		ax = 0.0f;
		vx = 0.0f;
		break;
	}
}

void CLifeForce::SetStateY(int state)
{
	switch (state)
	{
	case MARIO_STATE_RUNNING_UP:
		maxVy = -MARIO_RUNNING_SPEED;
		ay = -MARIO_ACCEL_RUN_Y;
		break;
	case MARIO_STATE_RUNNING_DOWN:
		maxVy = MARIO_RUNNING_SPEED;
		ay = MARIO_ACCEL_RUN_Y;
		break;
	case MARIO_STATE_WALKING_UP:
		maxVy = -MARIO_WALKING_SPEED;
		ay = -MARIO_ACCEL_WALK_Y;
		break;
	case MARIO_STATE_WALKING_DOWN:
		maxVy = MARIO_WALKING_SPEED;
		ay = MARIO_ACCEL_WALK_Y;
		break;
	case MARIO_STATE_IDLE:
		maxVy = 0.0f;
		ay = 0.0f;
		vy = 0.0f;
		break;
	}
}

void CLifeForce::SetState(int state)
{
	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
	case MARIO_STATE_RUNNING_LEFT:
	case MARIO_STATE_WALKING_RIGHT:
	case MARIO_STATE_WALKING_LEFT:
		SetStateX(state);
		break;

	case MARIO_STATE_RUNNING_UP:
	case MARIO_STATE_RUNNING_DOWN:
	case MARIO_STATE_WALKING_UP:
	case MARIO_STATE_WALKING_DOWN:
		SetStateY(state);
		break;

	case MARIO_STATE_IDLE:
		SetStateX(MARIO_STATE_IDLE);
		SetStateY(MARIO_STATE_IDLE);
		break;
	}

	CGameObject::SetState(state);
}
