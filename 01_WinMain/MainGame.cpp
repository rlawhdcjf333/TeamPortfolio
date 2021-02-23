#include "pch.h"
#include "MainGame.h"

#include "BackGround.h"
#include "Title.h"
#include "Home.h"
#include "PickBattle.h"
#include "LoadingScene.h"

void MainGame::Init()
{
	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);

	SceneManager::GetInstance()->AddScene(L"Title", new Title);
	SceneManager::GetInstance()->AddScene(L"Home", new Home);
	SceneManager::GetInstance()->AddScene(L"PickBattle", new PickBattle);
	SceneManager::GetInstance()->AddScene(L"LoadingScene", new LoadingScene);

	SceneManager::GetInstance()->LoadScene(L"LoadingScene");
}


void MainGame::Release()
{
	Random::ReleaseInstance();
	SoundPlayer::GetInstance()->Release();

	SafeDelete(mBackBuffer);
}

void MainGame::Update()
{
	SceneManager::GetInstance()->Update();
}

void MainGame::Render(HDC hdc)
{
	HDC backDC = mBackBuffer->GetHDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	{
		HFONT newF = (HFONT)GetStockObject(OEM_FIXED_FONT);
		HFONT oldF = (HFONT)SelectObject(hdc, newF);
		SceneManager::GetInstance()->Render(backDC);
		SelectObject(hdc, oldF);
		DeleteObject(newF);


	}
	mBackBuffer->Render(hdc, 0, 0);
}

void MainGame::RenderTime(HDC hdc)
{
	float worldTime = Time::GetInstance()->GetWorldTime();
	float deltaTime = Time::GetInstance()->DeltaTime();
	ULONG fps = Time::GetInstance()->GetmFrameRate();
	wstring strWorldTime = L"WorldTime : " + to_wstring(worldTime);
	wstring strDeltaTime = L"DeltaTime : " + to_wstring(deltaTime);
	wstring strFPS = L"FPS : " + to_wstring(fps);
	
	TextOut(hdc, 10, 10, strWorldTime.c_str(), strWorldTime.length());
	TextOut(hdc, 10, 25, strDeltaTime.c_str(), strDeltaTime.length());
	TextOut(hdc, 10, 40, strFPS.c_str(), strFPS.length());
}

