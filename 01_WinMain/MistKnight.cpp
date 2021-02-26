#include "pch.h"
#include "MistKnight.h"
#include "Animation.h"

MistKnight::MistKnight(const string& name)
	:Champ(name) 
{
	mChampName = L"MistKnight";
	mClassType = ClassType::Assassin;
}

void MistKnight::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"MistKnight", Resources(L"MistKnight.bmp"), 1680, 1680, 12, 12, true);
	mImage = IMAGEMANAGER->FindImage(L"MistKnight");
}

void MistKnight::Release()
{

}

void MistKnight::Update()
{

}

void MistKnight::Render(HDC hdc)
{

}


