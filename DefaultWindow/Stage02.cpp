#include "stdafx.h"
#include "Stage02.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "CScrollMgr.h"

#define scrollMgr CScrollMgr::Get_Instance()

CStage02::CStage02() : archer(nullptr), arrow(nullptr), power(0.0f)
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
	power = 0.0f;
	scrollMgr->Set_ScrollX(scrollMgr->Get_ScrollX() * -1);
}

void CStage02::Update()
{
	KeyManager::Get_Instance()->Update_Key();

	if (!arrow)
	{
		arrow = new Arrow();
		arrow->initalize();
		arrow->setPosition(archer->getPosition());
	}

	archer->update();

	if (!arrow->isShot())
	{
		arrow->setDirection(archer->getDirection());
	}
	arrow->update();

	int scroll = (int)(arrow->getPosition().x - scrollMgr->Get_ScrollX());
	scroll -= 400;
	if (abs(scroll) >= 5)
		scrollMgr->Set_ScrollX((float)scroll);

	if (scrollMgr->Get_ScrollX() < 0.0f)
		scrollMgr->Set_ScrollX(scrollMgr->Get_ScrollX() * -1.0f);
	else if (scrollMgr->Get_ScrollX() > 5000.0f)
		scrollMgr->Set_ScrollX(5000.0f + scrollMgr->Get_ScrollX() * -1.0f);


}

void CStage02::LateUpdate()
{

	if (arrow && !arrow->isShot())
	{
		if (KeyManager::Get_Instance()->Key_Pressing(VK_LBUTTON))
		{
			power += TimeManager::GetInstance().GetDeltaTime() * 200.0f;
		}
		else if (power >= 50.0f)
		{
			if (power >= 500.0f)
				power = 500.0f;

			arrow->shoot(power);
			power = 0.0f;
		}
		else
			power = 0.0f;
	}
	else if(arrow)
	{
		if (arrow->collision())
		{
			const D3DXVECTOR3* vertex = arrow->getVertex();
			DeadArrow* deadArrow = new DeadArrow();
			deadArrow->init(vertex[0], vertex[1]);
			deadArrows.push_back(deadArrow);
			delete arrow;
			arrow = nullptr;
		}
	}

}

void CStage02::Render(HDC _hdc)
{
	MoveToEx(_hdc, 0, 500, nullptr);
	LineTo(_hdc, 800, 500);


	MoveToEx(_hdc, (int)(1000.0f - scrollMgr->Get_ScrollX()), 300, nullptr);
	LineTo(_hdc, (int)(1000.0f - scrollMgr->Get_ScrollX()), 530);


	archer->render(_hdc);
	if(arrow)
		arrow->render(_hdc);

	for (auto deadArrow : deadArrows)
	{
		deadArrow->render(_hdc);
	}

}

void CStage02::Release()
{
	if (archer)
	{
		delete archer;
		archer = nullptr;
	}
	if (arrow)
	{
		delete arrow;
		arrow = nullptr;
	}

	for (auto& deadArrow : deadArrows)
	{
		delete deadArrow;
	}
	deadArrows.clear();

	CScrollMgr::Destroy_Instance();
}
