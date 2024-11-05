#include "stdafx.h"
#include "Stage01.h"

#include "Obj.h"


CStage01::CStage01(): mKeyManager(nullptr)
{
}

CStage01::~CStage01()
{
}

void CStage01::Initialize()
{
	mKeyManager = KeyManager::Get_Instance();
}

void CStage01::Update()
{
	mKeyManager->Update_Key();
}

void CStage01::LateUpdate()
{
}

void CStage01::Render(HDC _hdc)
{
}

void CStage01::Release()
{
	for (auto& obj : mObjects)
	{
		delete obj;
	}
}
