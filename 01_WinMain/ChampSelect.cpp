#include "pch.h"
#include "ChampSelect.h"

<<<<<<< HEAD
ChampSelect::ChampSelect() : UI ("ChampSelect")
{
	mIsActive = false;
=======
ChampSelect::ChampSelect()
	:UI("ChampSelect")
{
>>>>>>> 0c142ff0da6d8857d4b277bde53b17f8cc5ab4d6
ChampSelect::ChampSelect()
	:UI("ChampSelect")
{
}

void ChampSelect::Init()
{
<<<<<<< HEAD
	IMAGEMANAGER->LoadFromFile(L"BackFrame", Resources(L"ChampBack.bmp"), 308, 105, 4, 1, true);
	mBackFrame = IMAGEMANAGER->FindImage(L"BackFrame");

	mChampList = ChampManager::GetInstance()->GetChampList();
=======
>>>>>>> 0c142ff0da6d8857d4b277bde53b17f8cc5ab4d6
=======
>>>>>>> 0c142ff0da6d8857d4b277bde53b17f8cc5ab4d6
}

void ChampSelect::Release()
{
}

void ChampSelect::Update()
{
<<<<<<< HEAD
<<<<<<< HEAD
	if (!mIsActive)
		return;


=======
>>>>>>> 0c142ff0da6d8857d4b277bde53b17f8cc5ab4d6
=======
>>>>>>> 0c142ff0da6d8857d4b277bde53b17f8cc5ab4d6
}

void ChampSelect::Render(HDC hdc)
{
<<<<<<< HEAD

}

int ChampSelect::SetIndexX()
{
	return 0;
=======
>>>>>>> 0c142ff0da6d8857d4b277bde53b17f8cc5ab4d6
=======
>>>>>>> 0c142ff0da6d8857d4b277bde53b17f8cc5ab4d6
}
