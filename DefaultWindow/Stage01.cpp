#include "stdafx.h"
#include "Stage01.h"

#include "KeyManager.h"
#include "Obj.h"
#include "Pikachu.h"


CStage01::CStage01(): mKeyManager(nullptr)
{
}

CStage01::~CStage01()
{
	CStage01::Release();
}

void CStage01::Initialize()
{
	mKeyManager = KeyManager::Get_Instance();
	// Objects �߰��ϱ�
	mObjects.push_back(new Pikachu());
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