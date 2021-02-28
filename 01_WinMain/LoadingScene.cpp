#include "pch.h"
#include "LoadingScene.h"
#include "Image.h"
#include "Director.h"

void LoadingScene::AddLoadFunc(const function<void(void)>& func)
{
	mLoadList.push_back(func);
}

void LoadingScene::Init()
{
	mLoadIndex = 0;
	mIsEndLoading = false;

	IMAGEMANAGER->LoadFromFile(L"LoadingScene", Resources(L"LoadingScene.bmp"), 300, 233, false);
	mImage = IMAGEMANAGER->FindImage(L"LoadingScene");


	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"Warriors", L"../04_Bgm/Warriors.mp3", true); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"BanPick", L"../04_Bgm/BanPick.mp3", true); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"Warsong", L"../04_Bgm/Warsong.mp3", true); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"Airman", L"../04_Bgm/Airman.mp3", true); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"Pick", L"../04_Bgm/Pick.mp3", false); });
	AddLoadFunc([]() {ScheduleManager::GetInstance()->Init();});
	AddLoadFunc([]() {ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director1", L"TeamNuguri", L"TeamNuguri"));});
	AddLoadFunc([]() {ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director2", L"TeamMansu", L"TeamMansu"));});
	AddLoadFunc([]() {ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director3", L"TeamJoyRoom", L"TeamJoyRoom"));});
	AddLoadFunc([]() {ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director4", L"TeamCowHead", L"TeamCowHead"));});
	AddLoadFunc([]() {ObjectManager::GetInstance()->LoadInit();});


	for (int i = 0; i < 50; i++) {AddLoadFunc([](){});} //딜레이 0.5초를 위한 뻥펑터
	for (int i = 0; i < 50; i++) { AddLoadFunc([]() {}); } //딜레이 0.5초를 위한 뻥펑터


}

void LoadingScene::Release()
{
	ObjectManager::GetInstance()->Release();
}

void LoadingScene::Update()
{
	if (mLoadIndex >= mLoadList.size())
	{
		mIsEndLoading = true;

		SceneManager::GetInstance()->LoadScene(L"Title");

		return;
	}


	if (mLoadIndex > mLoadList.size() * 1 / 4) { mLoadingMessage = L"감독 선발 중..."; }
	if (mLoadIndex > mLoadList.size() * 2 / 4) {mLoadingMessage = L"선수 모집 중...";  }
    if (mLoadIndex > mLoadList.size() * 3 / 4) {mLoadingMessage = L"구단 등록 중...";  }

	function<void(void)> func = mLoadList[mLoadIndex];
	func();
	mLoadIndex++;

	mAlpha = (float)mLoadIndex / mLoadList.size();
}

void LoadingScene::Render(HDC hdc)
{
	RECT backGround = { 0,0, 1280, 720 };

	HBRUSH newb = (HBRUSH)GetStockObject(4);
	HBRUSH oldb = (HBRUSH)SelectObject(hdc, newb);
	RenderRect(hdc, backGround);
	SelectObject(hdc, oldb);
	DeleteObject(newb);

	RECT rc = { 550, WINSIZEY / 2 +200, 730, WINSIZEY / 2 +230 };
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	DrawTextW(hdc, mLoadingMessage.c_str(), mLoadingMessage.size(), &rc, DT_CENTER && DT_VCENTER);


	mImage->AlphaRender(hdc, WINSIZEX / 2 - mImage->GetWidth()/2, WINSIZEY / 2 - mImage->GetHeight()/2, mAlpha);
}
