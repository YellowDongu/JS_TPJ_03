#include "stdafx.h"
#include "Stage01.h"

#include "Ball.h"
#include "KeyManager.h"
#include "Obj.h"
#include "Pikachu.h"


CStage01::CStage01(): mKeyManager(nullptr)
{
}

CStage01::~CStage01()
{
	//CStage01::Release();
}

void CStage01::Initialize()
{
	mKeyManager = KeyManager::Get_Instance();
	// Objects 추가하기
	Pikachu* p1 = new Pikachu(0);
	Pikachu* p2 = new Pikachu(1);
	mObjects.push_back(p1);
	mObjects.push_back(p2);
	mObjects.push_back(new Ball(p1, p2));

	for(auto& obj : mObjects)
	{
		obj->Initialize();
	}
}

void CStage01::Update()
{
	UpdateObjects();
}

void CStage01::LateUpdate()
{
	LateUpdateObjects();
	mKeyManager->Update_Key();
}

void CStage01::Render(HDC _hdc)
{
	RenderObjects(_hdc);
	Rectangle(_hdc, WINCX / 2 - 10, WINCY - 250, WINCX / 2 + 10, WINCY);
}

void CStage01::Release()
{
	for (auto& obj : mObjects)
	{
		delete obj;
	}
}


#pragma region Objects
void CStage01::UpdateObjects() const
{
	for (auto& obj : mObjects)
	{
		obj->Update();
	}
}

void CStage01::LateUpdateObjects() const
{
	for (auto& obj : mObjects)
	{
		obj->LateUpdate();
	}
}

void CStage01::RenderObjects(HDC _hdc) const
{
	for (auto& obj : mObjects)
	{
		obj->Render(_hdc);
	}
}
#pragma endregion