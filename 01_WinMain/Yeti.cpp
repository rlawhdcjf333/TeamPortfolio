#include "pch.h"
#include "Yeti.h"

Yeti::Yeti(const string& name)
	:Champ(name) 
{
	mChampName = L"Yeti";
	mClassType = ClassType::Warrior;
}

void Yeti::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Yeti", Resources(L"Tanker1.bmp"), 2700, 2760, 9, 12, true);
	mImage = IMAGEMANAGER->FindImage(L"Yeti");
}

void Yeti::Release()
{
}

void Yeti::Update()
{
}

void Yeti::Render(HDC hdc)
{
}
