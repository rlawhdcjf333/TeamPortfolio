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
