#pragma once
#include "GameObject.h"

class Background : public GameObject
{

	wstring mFileName;
	Image* mImage;

public:
	Background(const string& name, const wstring& fileName);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};


