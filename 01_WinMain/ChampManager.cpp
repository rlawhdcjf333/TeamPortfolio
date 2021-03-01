#include "pch.h"
#include "ChampManager.h"
#include "Yeti.h"
#include "Pepe.h"
#include "Pixie.h"
#include "Tank.h"
#include "BubbleTea.h"
#include "LoveMonkey.h"
#include "ZombieMonkey.h"
#include "Cornian.h"
#include "MistKnight.h"

void ChampManager::Init()
{
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new Yeti("Champ1"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new Pepe("Champ2"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new Pixie("Champ3"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new Tank("Champ4"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new BubbleTea("Champ5"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new ZombieMonkey("Champ6"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new LoveMonkey("Champ7"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new MistKnight("Champ8"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new Cornian("Champ9"));

	for (int i = 0; i < 9; i++) {
		mChampList.push_back(ObjectManager::GetInstance()->FindObject("Champ" + to_string(i + 1)));
		mChampList[i]->SetIsActive(false);
	}
}

void ChampManager::SceneRelease()
{
	mChampList.clear();
	mChampList.shrink_to_fit();
}

void ChampManager::Release()
{
	for (int i = 0; i < mChampList.size(); i++) {
		mChampList[i]->Init();
	}
}

void ChampManager::Update()
{
}

void ChampManager::Render(HDC hdc)
{
	for (int i = 0; i < mChampList.size(); i++) {
		mChampList[i]->Render(hdc);
	}
}
