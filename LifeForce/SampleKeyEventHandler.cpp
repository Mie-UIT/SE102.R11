#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "LifeForce.h"
#include "Bullet.h"

extern CLifeForce* mario;
extern vector<LPGAMEOBJECT> objects;

#define MAX_ACTIVE_BULLETS 4

int CountActiveBullets()
{
	int count = 0;
	for (int i = 0; i < (int)objects.size(); i++)
	{
		CBullet* bullet = dynamic_cast<CBullet*>(objects[i]);
		if (bullet != NULL && bullet->IsActive())
		{
			count++;
		}
	}
	return count;
}

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
	case DIK_S:
		if (mario != NULL && CountActiveBullets() < MAX_ACTIVE_BULLETS)
		{
			float x, y;
			mario->GetPosition(x, y);
			CBullet* bullet = new CBullet(x + 20.0f, y);
			objects.push_back(bullet);
		}
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	CGame* game = CGame::GetInstance();

	// Điều khiển theo phương ngang (Trái / Phải)
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetStateX(MARIO_STATE_RUNNING_RIGHT);
		else
			mario->SetStateX(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetStateX(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetStateX(MARIO_STATE_WALKING_LEFT);
	}
	else
	{
		mario->SetStateX(MARIO_STATE_IDLE);
	}

	// Điều khiển theo phương dọc (Lên / Xuống)
	if (game->IsKeyDown(DIK_UP))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetStateY(MARIO_STATE_RUNNING_UP);
		else
			mario->SetStateY(MARIO_STATE_WALKING_UP);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetStateY(MARIO_STATE_RUNNING_DOWN);
		else
			mario->SetStateY(MARIO_STATE_WALKING_DOWN);
	}
	else
	{
		mario->SetStateY(MARIO_STATE_IDLE);
	}
}
