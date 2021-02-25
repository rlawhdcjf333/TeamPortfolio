#include "pch.h"
#include "GameObject.h"


GameObject::GameObject()
	:mIsActive(true), mIsDestroy(false) {}

GameObject::GameObject(const string & name)
	: mName(name), mIsActive(true), mIsDestroy(false) {}

void GameObject::Init()
{
}

void GameObject::Release()
{
}

void GameObject::Update()
{
}

void GameObject::Render(HDC hdc)
{
}

GameObject::GameObject(const GameObject & copy)
{
	mName = copy.mName;
	mX = copy.mX;
	mY = copy.mY;
	mSizeX = copy.mSizeX;
	mSizeY = copy.mSizeY;
	mRect = copy.mRect;
	mIsActive = copy.mIsActive;
	mIsDestroy = copy.mIsDestroy;
}

GameObject& GameObject::operator=(const GameObject & copy)
{

	mName = copy.mName;
	mX = copy.mX;
	mY = copy.mY;
	mSizeX = copy.mSizeX;
	mSizeY = copy.mSizeY;
	mRect = copy.mRect;
	mIsActive = copy.mIsActive;
	mIsDestroy = copy.mIsDestroy;


	return *this;
}
