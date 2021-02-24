#include "pch.h"
#include "Storage.h"
#include "GameObject.h"
#include "Director.h"
#include "Staff.h"

Storage::Storage()
{
	for (int i = 0; i < (int)ObjectLayer::End; ++i)
	{
		vector<GameObject*> emptyVector;
		mObjectList.insert(make_pair((ObjectLayer)i, emptyVector));
	}
}

void Storage::Clear()
{
	ObjectIter iter = mObjectList.begin();
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

void Storage::CopyToStorage(map <ObjectLayer, vector <GameObject*>> list)
{
	ObjectIter iter = list.begin();

	for (; iter != list.end(); iter++)
	{

		if (iter->first == ObjectLayer::Director)
		{
			for (int i = 0; i < iter->second.size(); ++i) {

				if (FindObject(iter->second[i]->GetName()) == nullptr) //저장소에 찾아봤는데 그런 이름을 가진 친구가 없음
				{
					Director* tmp = (Director*)iter->second[i]; //다운 캐스트 해서
					Director* copy = new Director(*tmp); //이걸 복사생성자로 복사해서
					AddObject(iter->first, copy);  //저장소에 새로 등록
				}
				else // 이미 그런 이름을 가진 애가 있음
				{
					ElemSwap(ObjectLayer::Director, iter->second[i]);
				}
			}

		}

		if (iter->first == ObjectLayer::Staff)
		{
			for (int i = 0; i < iter->second.size(); ++i) {

				if (FindObject(iter->second[i]->GetName()) == nullptr) //저장소에 없음
				{
					Staff* tmp = (Staff*)iter->second[i]; //다운 캐스트 해서
					Staff copy = *tmp; //이걸 복사 생성자로 복사해서
					AddObject(iter->first, &copy);  //저장소에 새로 등록

				}
				else // 저장소에 있네?
				{
					ElemSwap(ObjectLayer::Staff, iter->second[i]);
				}
			}
		}
	}

}

void Storage::CopyFromStorage(map <ObjectLayer, vector <GameObject*>> list)
{
	ObjectIter iter = list.begin();

	for (; iter != list.end(); iter++)
	{
		if (iter->first == ObjectLayer::Director)
		{
			for (int i = 0; i < iter->second.size(); ++i) {

				if (FindObject(iter->second[i]->GetName()) != nullptr) // 저장소에 같은 이름으로 된 데이터가 존재하면
				{
					GameObject* origin = FindObject(iter->second[i]->GetName()); // 저장소 데이터 찾아다가
					Director *tmp = (Director*)origin; //다운캐스팅
					Director copy = *tmp; // 복사

					GameObject* newData = iter->second[i]; //새로 만들어진 데이터 임시캐싱
					SafeDelete(newData);  //지워주고
					newData = &copy; //저장소 데이터로 갱신
				}
			}

		}


		if (iter->first == ObjectLayer::Staff)
		{
			for (int i = 0; i < iter->second.size(); ++i) {
				if (FindObject(iter->second[i]->GetName()) != nullptr) // 저장소에 같은 이름으로 된 데이터가 존재하면
				{
					GameObject* origin = FindObject(iter->second[i]->GetName()); // 저장소 데이터 찾아다가
					Staff *tmp = (Staff*)origin; //다운캐스팅
					Staff copy = *tmp; // 복사

					GameObject* newData = iter->second[i]; //새로 만들어진 데이터 임시캐싱
					newData->Release();
					SafeDelete(newData);  //지워주고
					newData = &copy; //저장소 데이터로 갱신
				}
			}
		}
	}



}

void Storage::ElemSwap(ObjectLayer layerName, GameObject * origin)
{

	auto& tmp = mObjectList[layerName];

	for (GameObject*& elem : tmp)
	{
		if (elem->GetName() == origin->GetName())
		{
			elem->Release();
			SafeDelete(elem);

			if (layerName == ObjectLayer::Director)
			{
				Director* pTmp = (Director*)elem;
				Director *copy = new Director(*pTmp);
					
				elem = copy;
			}

			else if (layerName == ObjectLayer::Staff)
			{
				Staff* pTmp = (Staff*)elem;
				Staff *copy = new Staff(*pTmp);

				elem = copy;
			}
		}

	}



}


