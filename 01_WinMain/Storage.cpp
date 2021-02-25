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

				if (FindObject(iter->second[i]->GetName()) == nullptr) //����ҿ� ã�ƺôµ� �׷� �̸��� ���� ģ���� ����
				{
					Director* tmp = (Director*)iter->second[i]; //�ٿ� ĳ��Ʈ �ؼ�
					Director* copy = new Director(*tmp); //�̰� ��������ڷ� �����ؼ�
					AddObject(iter->first, copy);  //����ҿ� ���� ���
				}
				else // �̹� �׷� �̸��� ���� �ְ� ����
				{
					ElemSwap(ObjectLayer::Director, iter->second[i]);
				}
			}

		}

		if (iter->first == ObjectLayer::Staff)
		{
			for (int i = 0; i < iter->second.size(); ++i) {

				if (FindObject(iter->second[i]->GetName()) == nullptr) //����ҿ� ����
				{
					Staff* tmp = (Staff*)iter->second[i]; //�ٿ� ĳ��Ʈ �ؼ�
					Staff* copy = new Staff(*tmp); //�̰� ���� �����ڷ� �����ؼ�
					AddObject(iter->first, copy);  //����ҿ� ���� ���

				}
				else // ����ҿ� �ֳ�?
				{
					ElemSwap(ObjectLayer::Staff, iter->second[i]);
				}
			}
		}
	}

}


void Storage::ElemSwap(ObjectLayer layerName, GameObject* origin)
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
				Director* pTmp = (Director*)origin;
				Director *copy = new Director(*pTmp);
					
				elem = copy;
			}

			if (layerName == ObjectLayer::Staff)
			{
				Staff* pTmp = (Staff*)origin;
				Staff *copy = new Staff(*pTmp);

				elem = copy;
			}
		}

	}



}


