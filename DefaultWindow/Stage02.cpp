#include "stdafx.h"
#include "Stage02.h"
#include "KeyManager.h"
#include "TimeManager.h"
CStage02::CStage02()
{
}

CStage02::~CStage02()
{
}

void CStage02::Initialize()
{
	archer = new Archer();
	archer->initalize();

	arrow = new Arrow();
	arrow->initalize();
	arrow->setPosition(archer->getPosition());
}

void CStage02::Update()
{
	archer->update();
	if (!arrow->isShot())
	{
		arrow->setDirection(archer->getDirection());
	}
	arrow->update();
}

void CStage02::LateUpdate()
{

	//if (!arrow->isShot())
	//{
	//	if (KeyManager::Get_Instance()->Key_Pressing(VK_LBUTTON))
	//	{
	//		power += TimeManager::GetInstance().GetDeltaTime() * 100.0f;
	//	}
	//	else if (KeyManager::Get_Instance()->Key_Up(VK_LBUTTON))
	//	{
	//		if (power >= 500.0f)
	//			power = 500.0f;
	//		arrow->shoot(power);
	//	}
	//}


}

void CStage02::Render(HDC _hdc)
{
	archer->render(_hdc);
	arrow->render(_hdc);
}

void CStage02::Release()
{
	delete archer;
	archer = nullptr;
		  
	delete arrow;
	arrow = nullptr;
}
