#include "pch.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "Director.h"
#include "Staff.h"
#include <algorithm>

ObjectManager::ObjectManager()
{
	for (int i = 0; i < (int)ObjectLayer::End; ++i)
	{
		vector<GameObject*> emptyVector;
		mObjectList.insert(make_pair((ObjectLayer)i, emptyVector));
	}
}


void ObjectManager::Init()
{
	for (int i = 1; i < 5; i++)
	{
		Director* tmp = (Director*)Storage::GetInstance()->FindObject("Director" + to_string(i));
		Director* copy = new Director(*tmp);
		AddObject(ObjectLayer::Director, copy);
	}

	auto tmp = Storage::GetInstance()->GetObjectList(ObjectLayer::Staff);
	for (int i = 0; i < Storage::GetInstance()->GetObjectList(ObjectLayer::Staff).size(); i++)
	{
		Staff* tempo = (Staff*)tmp[i];
		Staff* copy = new Staff(*tempo);
		AddObject(ObjectLayer::Staff, copy);
	}


	ObjectIter iter = mObjectList.begin();
	
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->first == ObjectLayer::Director) continue;
			if (iter->first == ObjectLayer::Staff) continue;

			iter->second[i]->Init();
		}
	}

	

}

void ObjectManager::LoadInit()
{
	ObjectIter iter = mObjectList.begin();

	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->Init();

		}
	}
}

void ObjectManager::Release()
{
	ObjectIter iter = mObjectList.begin();
	Storage::GetInstance()->CopyToStorage(mObjectList);

	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->Release();
			SafeDelete(iter->second[i]);
		}

		iter->second.clear();
		iter->second.shrink_to_fit();
	}
	
}


void ObjectManager::Update()
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetIsDestroy() == true)
			{
				iter->second[i]->Release();
				SafeDelete(iter->second[i]);
				iter->second.erase(iter->second.begin() + i);
				--i;
				continue;
			}
			if (iter->second[i]->GetIsActive() == true)
			{
				iter->second[i]->Update();
			}
		}
	}
}

void ObjectManager::Render(HDC hdc)
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetIsActive() == true)
			{
				iter->second[i]->Render(hdc);
			}
		}
	}
}

void ObjectManager::AddObject(ObjectLayer layer, GameObject * object)
{
	mObjectList[layer].push_back(object);
}

GameObject * ObjectManager::FindObject(const string & name)
{
	ObjectIter iter = mObjectList.begin();

	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetName() == name)
			{
				return iter->second[i];
			}
		}
	}
	return nullptr;
}

GameObject * ObjectManager::FindObject(ObjectLayer layer, const string & name)
{
	ObjectIter iter = mObjectList.find(layer);
	for (int i = 0; i < iter->second.size(); ++i)
	{
		if (iter->second[i]->GetName() == name)
		{
			return iter->second[i];
		}
	}
	return nullptr;
}

vector<class GameObject*> ObjectManager::FindObjects(const string & name)
{
	vector<GameObject*> result;

	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetName() == name)
			{
				result.push_back(iter->second[i]);
			}
		}
	}

	return result;
}

vector<class GameObject*> ObjectManager::FindObjects(ObjectLayer layer, const string & name)
{
	vector<GameObject*> result;
	ObjectIter iter = mObjectList.find(layer);
	for (int i = 0; i < iter->second.size(); ++i)
	{
		if (iter->second[i]->GetName() == name)
		{
			result.push_back(iter->second[i]); 
		}
	}
	return result;
}

vector<class GameObject*> ObjectManager::GetObjectList(ObjectLayer layer)
{
	return mObjectList[layer];
}

void ObjectManager::OriginSwap(ObjectLayer layerName, GameObject * old)
{
	// 그냥... 우리 CTO가 남긴 고민의 흔적 ㅠㅠ
	auto& tmp = mObjectList[layerName];

	for (GameObject*& elem : tmp)
	{
		if (elem->GetName() == old->GetName())
		{
			elem->Release();
			SafeDelete(elem); //비워주고

			if (layerName == ObjectLayer::Director)
			{
				Director* pTmp = (Director*) old; // 다운캐스팅
				Director *copy = new Director(*pTmp); // 복사 ㄱㄱ
			
				elem = copy;
				
			}
		
			if (layerName == ObjectLayer::Staff)
			{
				Staff* pTmp = (Staff*)old; // 다운캐스팅
				Staff *copy = new Staff(*pTmp); // 복사 ㄱㄱ

				elem = copy;

			}
		}
	}
		
}

void ObjectManager::Zorder()
{
	auto func = [](GameObject* a, GameObject* b)
	{
		if (a->GetX() == b->GetY()) //증말 흔치 않은 일이지만 이럴수도 있지
		{
			return a->GetName() < a->GetName();
		}
		return a->GetY() < b->GetY();
	};
	sort(mObjectList[ObjectLayer::Champ].begin(), mObjectList[ObjectLayer::Champ].end(), func);

}

void ObjectManager::ReInitChamp()
{
	for (GameObject* elem : mObjectList[ObjectLayer::Champ])
	{
		elem->Init();
	}
}

void ObjectManager::ChampClear()
{
	for (GameObject*& elem : mObjectList[ObjectLayer::Champ])
	{
		elem->Release();
		SafeDelete(elem);
	}

	mObjectList[ObjectLayer::Champ].clear();
	mObjectList[ObjectLayer::Champ].shrink_to_fit();

}


vector<string> ObjectManager::GetPlayOff()
{
	vector<Director*> result;

	auto list = mObjectList[ObjectLayer::Director];

	for (GameObject* elem : list)
	{
		Director* dir = (Director*)elem;
		result.push_back(dir);
	}

	auto func = [](Director* a, Director* b)
	{
		if (a->GetLeagueScore() == b->GetLeagueScore())
		{
			return a->GetName() < b->GetName();
		}
		return a->GetLeagueScore() > b->GetLeagueScore();
	};

	sort(result.begin(), result.end(), func);
	result.pop_back();
	result.pop_back();

	vector <string> realResult;
	realResult.push_back(result[0]->GetName());
	realResult.push_back(result[1]->GetName());
	realResult.push_back(result[2]->GetName());
	realResult.push_back(result[3]->GetName());

	return realResult;
}







