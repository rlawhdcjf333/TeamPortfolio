#include "pch.h"
#include "MainGame.h"

#include "BackGround.h"
#include "Title.h"
#include "Home.h"
#include "Pick_Battle.h"
#include "LoadingScene.h"

void MainGame::Init()
{
	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);

	SceneManager::GetInstance()->AddScene(L"Title", new Title);
	SceneManager::GetInstance()->AddScene(L"Home", new Home);
	SceneManager::GetInstance()->AddScene(L"Pick_Battle", new Pick_Battle);
	SceneManager::GetInstance()->AddScene(L"LoadingScene", new LoadingScene);

	SceneManager::GetInstance()->LoadScene(L"LoadingScene");
}


void MainGame::Release()
{
	Random::ReleaseInstance();

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
		SceneManager::GetInstance()->Render(backDC);
		//Image* image = IMAGEMANAGER->FindImage(L"Title");
		//if(image)
		//	image->ScaleRender(backDC, 0, 0, 300, 300);
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

