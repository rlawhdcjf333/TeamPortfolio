#include "pch.h"
#include "Storage.h"
#include "GameObject.h"

Storage::Storage()
{
	for (int i = 0; i < (int)ObjectLayer::End; ++i)
	{
		vector<GameObject*> emptyVector;
		mObjectList.insert(make_pair((ObjectLayer)i, emptyVector));
	}
}


