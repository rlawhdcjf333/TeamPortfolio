#include "pch.h"
#include "Director.h"
#include "Staff.h"

//vector<string> Director::Name;

Director::Director(const string& name, const wstring& fileName, const wstring& teamName)
	:GameObject(name)
{
	mTeamName = teamName;
	mFileName = fileName;
	mIsActive = false;
}

// 굳이 감독 캐릭터가 필요할까??
// 팀이름
// TeamNuguri, TeamMansu, TeamJoyRoom, TeamCowHead
void Director::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(mFileName, Resources(mFileName + L".bmp"), 60, 60, true);
	mTeamImage = IMAGEMANAGER->GetInstance()->FindImage(mFileName);

	mGold = Random::GetInstance()->RandomInt(100, 500);
	mWeek = 1;
	mMonth = 1;

	mWin = 0;
	mLose = 0;

	for (int i = 0; i < 3; i++) {
		mStaffNameList.push_back(RandomName());
	}
	
	if (mTeamName == L"TeamNuguri") {
		mStaffNameList.push_back(RandomName());
	}

	for (int i=0; i<mStaffNameList.size(); i++)
	{
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Staff, new Staff(mStaffNameList[i], mStaffNameList[i], mTeamName));
	}
	// Staff 클래스의 생성자를 확인하기 바랍니다. -CTO
	
	//for (string name : mStaffNameList) {
	//	ObjectManager::GetInstance()->FindObject(name)->Init();
	//}
	// AddObject돌리셨으면 굳이 Init() 돌릴 필요가 음슴니다. scene init에서 일괄적으로 돌리기 때문이죠. 이러면 Init()이 두번 돕니다 -CTO

	//ObjectManager::GetInstance()->FindObject(str1)->Init();
	//ObjectManager::GetInstance()->FindObject(str2)->Init();
	//ObjectManager::GetInstance()->FindObject(str3)->Init();
}

void Director::Release()
{

}

void Director::Update()
{
	mLeagueScore = mWin * 3 + mLose;

}

void Director::Render(HDC hdc)
{
	if (mIsActive) {
		mTeamImage->ScaleRender(hdc, mX, mY, mTeamImage->GetFrameWidth(), mTeamImage->GetFrameHeight());
	}
}


void Director::UIRender(HDC hdc, int startX, int startY, int width, int height)
{

	mTeamImage->ScaleRender(hdc, startX, startY, width, height);

	RECT calendarRc = RectMake(860, 10, 160, 50);
	RECT goldRc = RectMake(1100, 10, 160, 50);
	RECT recordRc = RectMake(90, 40, 130, 30);
	
	HFONT newF = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	HFONT oldF = (HFONT) SelectObject(hdc, newF);

	TextOut(hdc, 90, 10, mTeamName.c_str(), mTeamName.length());
	wstring str = L"2021년  " + to_wstring(mMonth) + L"월  " + to_wstring(mWeek) + L"주차";
	DrawText(hdc, str.c_str(), str.size(), &calendarRc, DT_VCENTER | DT_RIGHT | DT_SINGLELINE);
	wstring str1 = to_wstring(mGold);
	DrawText(hdc, str1.c_str(), str1.size(), &goldRc, DT_VCENTER | DT_RIGHT | DT_SINGLELINE);
	wstring str2 = L"?위  " + to_wstring(mWin) + L"승  " + to_wstring(mLose) + L"패  +" + to_wstring(mLeagueScore);
	DrawText(hdc, str2.c_str(), str2.size(), &recordRc, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

	SelectObject(hdc, oldF);
	DeleteObject(newF);

}

Director::Director(const Director & copy)
	:GameObject(copy)
{
	mRandomNameList = copy.mRandomNameList;

	mTeamImage = copy.mTeamImage;
	mFileName = copy.mFileName;
	mTeamName = copy.mTeamName;
	mMonth = copy.mMonth;
	mWeek = copy.mWeek;
	mGold = copy.mGold;

	mWin = copy.mWin;
	mLose = copy.mLose;
	mLeagueScore = copy.mLeagueScore;

	mStaffNameList = copy.mStaffNameList;

}

Director & Director::operator=(const Director & copy)
{
	mRandomNameList = copy.mRandomNameList;

	mTeamImage = copy.mTeamImage;
	mFileName = copy.mFileName;
	mTeamName = copy.mTeamName;
	mMonth = copy.mMonth;
	mWeek = copy.mWeek;
	mGold = copy.mGold;

	mWin = copy.mWin;
	mLose = copy.mLose;
	mLeagueScore = copy.mLeagueScore;

	mStaffNameList = copy.mStaffNameList;



	return *this;
}

string Director::RandomName()
{
	if (mRandomNameList.size() == 0)
	{
		mRandomNameList.push_back("KSW");
		mRandomNameList.push_back("Banana");
		mRandomNameList.push_back("Crom");
		mRandomNameList.push_back("Jake");
		mRandomNameList.push_back("Sam");
		mRandomNameList.push_back("HobakGoguma");
		mRandomNameList.push_back("Lockman");
		mRandomNameList.push_back("Wa");
		mRandomNameList.push_back("Maple");
		mRandomNameList.push_back("Mr.Kyugil");
		mRandomNameList.push_back("Ppangkkuttongkku");
		mRandomNameList.push_back("Gonjaless");
		mRandomNameList.push_back("Mario");
		mRandomNameList.push_back("MG the God");
		mRandomNameList.push_back("Takara");
		mRandomNameList.push_back("Kakao");
		mRandomNameList.push_back("Lion");
		mRandomNameList.push_back("Zelda");
		mRandomNameList.push_back("Github");
		mRandomNameList.push_back("Donggass");
		mRandomNameList.push_back("Erum");
		mRandomNameList.push_back("Jerry");
		mRandomNameList.push_back("Tom");
		mRandomNameList.push_back("Kwangsub");
		mRandomNameList.push_back("GHAAA");
		mRandomNameList.push_back("Vecx");
		mRandomNameList.push_back("NuguryMaster");
		mRandomNameList.push_back("Bryndi");
		mRandomNameList.push_back("Eksomess");
		mRandomNameList.push_back("Gwawle");
		mRandomNameList.push_back("Igandir");
		mRandomNameList.push_back("Iteric");
		mRandomNameList.push_back("Jarrite");
		mRandomNameList.push_back("Korten");
		mRandomNameList.push_back("cidy sizer makes my feel hight");
		mRandomNameList.push_back("Umilum");
		mRandomNameList.push_back("Webbitus");
		mRandomNameList.push_back("Nugu");
		mRandomNameList.push_back("Emetshelk");
		mRandomNameList.push_back("Danice");
		mRandomNameList.push_back("Edward Elic");
		mRandomNameList.push_back("CommitPushij-jima");
		mRandomNameList.push_back("Jumsimnagasumukulgugodhea");
		mRandomNameList.push_back("Laliho");
		mRandomNameList.push_back("Cloy");
		mRandomNameList.push_back("Bob");
		mRandomNameList.push_back("Brave Cookie");
		mRandomNameList.push_back("Gardian");
		mRandomNameList.push_back("Faker");
		mRandomNameList.push_back("Last");
	}

	int index = Random::GetInstance()->RandomInt(mRandomNameList.size());
	string name = mRandomNameList[index];
	mRandomNameList.erase(mRandomNameList.begin() + index);
	return name;
}