#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_ACCEL_WALK_Y	0.0005f
#define MARIO_ACCEL_RUN_Y	0.0007f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_WALKING_UP		300
#define MARIO_STATE_WALKING_DOWN	350

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500
#define MARIO_STATE_RUNNING_UP		600
#define MARIO_STATE_RUNNING_DOWN	700


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#pragma endregion

class CLifeForce : public CGameObject
{
	float maxVx;
	float ax;				// acceleration on x 
	float maxVy;
	float ay;				// acceleration on y 
public:
	CLifeForce(float x, float y) : CGameObject(x, y)
	{
		maxVx = 0.0f;
		ax = 0.0f;
		maxVy = 0.0f;
		ay = 0.0f;
	}
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	void SetStateX(int state);
	void SetStateY(int state);
};

typedef CLifeForce CMario;
