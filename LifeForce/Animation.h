#pragma once

#include <Windows.h>
#include <unordered_map>

#include "Sprites.h"
#include "AnimationFrame.h"


using namespace std;

class CAnimation
{
	ULONGLONG lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
	bool loop;
	bool finished;
public:
	CAnimation(int defaultTime, bool loop = true)
	{
		this->defaultTime = defaultTime;
		this->lastFrameTime = -1;
		this->currentFrame = -1;
		this->loop = loop;
		this->finished = false;
	}
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, float scale = 1.0f);
	void Reset() { currentFrame = -1; lastFrameTime = -1; finished = false; }
	bool IsFinished() { return finished; }
};

typedef CAnimation* LPANIMATION;
