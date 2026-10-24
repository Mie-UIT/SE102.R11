/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	LIFE FORCE - SPACESHIP SPRITE & KEYBOARD STATES
	(Based on Sample 03 - Keyboard and Object State)
================================================================ */

#include <windows.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Animation.h"
#include "Animations.h"
#include "Sprite.h"
#include "Sprites.h"

#include "LifeForce.h"
#include "Bullet.h"
#include "Enemy.h"

#include "SampleKeyEventHandler.h"


#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"LifeForce - Spaceship"
#define WINDOW_ICON_PATH L"mario.ico"


#define BACKGROUND_COLOR D3DXCOLOR(0.0f/255, 0.0f/255, 0.0f/255, 0.0f)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10

#define TEXTURES_DIR L"textures"
#define TEXTURE_PATH_MARIO TEXTURES_DIR "\\life_force.png"
#define TEXTURE_PATH_ENEMY TEXTURES_DIR "\\momonga.png"

#define MARIO_START_X 100.0f
#define MARIO_START_Y 100.0f

#define ENEMY_START_X 220.0f
#define ENEMY_START_Y 100.0f

CLifeForce* mario = NULL;
CEnemy* enemy = NULL;

CSampleKeyHandler* keyHandler;

vector<LPGAMEOBJECT> objects;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and spaceship (CMario) object
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MARIO, TEXTURE_PATH_MARIO);
	textures->Add(ID_TEX_ENEMY, TEXTURE_PATH_ENEMY);

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	
	LPTEXTURE texMario = textures->Get(ID_TEX_MARIO);
	LPTEXTURE texEnemy = textures->Get(ID_TEX_ENEMY);

	// Sprite phi thuyền đầu tiên từ life_force.png với tọa độ (56, 8) và (79, 23)
	sprites->Add(10001, 56, 8, 79, 23, texMario);

	LPANIMATION ani;

	ani = new CAnimation(100);	
	ani->Add(10001);
	animations->Add(ID_ANI_MARIO_IDLE_RIGHT, ani);

	// 3 sprites viên đạn từ life_force.png
	sprites->Add(ID_SPRITE_BULLET_1, 328, 8, 351, 23, texMario);
	sprites->Add(ID_SPRITE_BULLET_2, 352, 8, 375, 23, texMario);
	sprites->Add(ID_SPRITE_BULLET_3, 376, 8, 399, 23, texMario);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_BULLET_1);
	ani->Add(ID_SPRITE_BULLET_2);
	ani->Add(ID_SPRITE_BULLET_3);
	animations->Add(ID_ANI_BULLET, ani);

	// 7 sprites enermy từ momonga.png 
	sprites->Add(ID_SPRITE_ENEMY_1, 655, 338, 751, 435, texEnemy);
	sprites->Add(ID_SPRITE_ENEMY_2, 835, 335, 943, 436, texEnemy);
	sprites->Add(ID_SPRITE_ENEMY_3, 1010, 332, 1117, 440, texEnemy);
	sprites->Add(ID_SPRITE_ENEMY_4, 1195, 334, 1300, 440, texEnemy);
	sprites->Add(ID_SPRITE_ENEMY_5, 1382, 332, 1539, 441, texEnemy);
	sprites->Add(ID_SPRITE_ENEMY_6, 1563, 332, 1792, 441, texEnemy);
	sprites->Add(ID_SPRITE_ENEMY_7, 1770, 354, 1911, 440, texEnemy);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_ENEMY_1);
	animations->Add(ID_ANI_ENEMY_IDLE, ani);

	ani = new CAnimation(150, false);
	ani->Add(ID_SPRITE_ENEMY_2);
	ani->Add(ID_SPRITE_ENEMY_3);
	ani->Add(ID_SPRITE_ENEMY_4);
	ani->Add(ID_SPRITE_ENEMY_5);
	ani->Add(ID_SPRITE_ENEMY_6);
	ani->Add(ID_SPRITE_ENEMY_7);
	animations->Add(ID_ANI_ENEMY_DIE, ani);

	mario = new CLifeForce(MARIO_START_X, MARIO_START_Y);
	objects.push_back(mario);

	enemy = new CEnemy(ENEMY_START_X, ENEMY_START_Y);
	objects.push_back(enemy);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Update(dt);
	}

	if (enemy != NULL && !enemy->IsDead() && enemy->GetState() == ENEMY_STATE_IDLE)
	{
		float ex, ey;
		enemy->GetPosition(ex, ey);

		for (int i = 0; i < (int)objects.size(); i++)
		{
			CBullet* bullet = dynamic_cast<CBullet*>(objects[i]);
			if (bullet != NULL && bullet->IsActive())
			{
				float bx, by;
				bullet->GetPosition(bx, by);

				if (abs(bx - ex) <= (ENEMY_BBOX_WIDTH + BULLET_BBOX_WIDTH) / 2.0f &&
					abs(by - ey) <= (ENEMY_BBOX_HEIGHT + BULLET_BBOX_HEIGHT) / 2.0f)
				{
					bullet->Deactivate();
					enemy->SetState(ENEMY_STATE_DIE);
					break;
				}
			}
		}
	}
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

	spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

	FLOAT NewBlendFactor[4] = { 0,0,0,0 };
	pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Render();
	}

	spriteHandler->End();
	pSwapChain->Present(0, 0);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			CGame::GetInstance()->ProcessKeyboard();
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	SetDebugWindow(hWnd);

	CGame* game = CGame::GetInstance();
	game->Init(hWnd, hInstance);

	keyHandler = new CSampleKeyHandler();
	game->InitKeyboard(keyHandler);

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	LoadResources();

	Run();

	return 0;
}
