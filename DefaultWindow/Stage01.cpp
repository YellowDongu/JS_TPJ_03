#include "stdafx.h"
#include "Stage01.h"

#include "Ball.h"
#include "CBmpMgr.h"
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
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Sprite/Pikachu_BG.bmp", L"Pikachu_BG");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Sprite/Ball_Shadow.bmp", L"Ball_Shadow");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Sprite/Ball.bmp", L"Ball");


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
	BitBlt(_hdc,
		0, 0,
		800, 600,
		CBmpMgr::Get_Instance()->Find_Image(L"Pikachu_BG"),
		0, 0, SRCCOPY);
	RenderObjects(_hdc);
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