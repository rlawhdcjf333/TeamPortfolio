#include "pch.h"
#include "ChampManager.h"
#include "Yeti.h"
#include "HelmetPepe.h"
#include "StarPixie.h"
#include "Tank.h"
#include "BubbleTea.h"
#include "BabyMonkey.h"
#include "ZombieMonkey.h"
#include "BabyMonkey.h"
#include "Cornian.h"
#include "MistKnight.h"

void ChampManager::Init()
{
	//이걸 왜이렇게 어렵게 하고 있어?? 걍 champ* vector 만들어서 쓰면 되자너???

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new Yeti("Champ1"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new HelmetPepe("Champ2"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new StarPixie("Champ3"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new Tank("Champ4"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new BubbleTea("Champ5"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new ZombieMonkey("Champ6"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new BabyMonkey("Champ7"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new MistKnight("Champ8"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Champ, new Cornian("Champ9"));

	for (int i = 0; i < 9; i++) {
		mChampList.push_back(ObjectManager::GetInstance()->FindObject("Champ" + to_string(i + 1)));
		mChampList[i]->SetIsActive(false);
	}
}

void ChampManager::Release()
{
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
