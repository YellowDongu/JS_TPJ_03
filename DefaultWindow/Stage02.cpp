#include "stdafx.h"
#include "Stage02.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "CScrollMgr.h"
#include "SoundMgr.h"
#include "CBmpMgr.h"

#define scrollMgr CScrollMgr::Get_Instance()
#define soundMgr CSoundMgr::Get_Instance()
#define keyMgr KeyManager::Get_Instance()
#define Time TimeManager::GetInstance()

CStage02::CStage02() : archer(nullptr), arrow(nullptr), power(0.0f), time(0.0f)
,groundBrush(NULL),groundPen(NULL),skyBrush(NULL),skyPen(NULL)
{
}

CStage02::~CStage02()
{
}

void CStage02::Initialize()
{

	groundBrush = CreateSolidBrush(RGB(0, 200, 0));
	groundPen = CreatePen(PS_SOLID, 2, RGB(0, 200, 0));
	skyBrush = CreateSolidBrush(RGB(125, 200, 240));
	skyPen = CreatePen(PS_SOLID, 2, RGB(125, 200, 240));

	archer = new Archer();
	archer->initalize();

	arrow = new Arrow();
	arrow->initalize();
	arrow->setPosition(archer->getPosition());
	power = 0.0f;
	scrollMgr->Set_ScrollX(scrollMgr->Get_ScrollX() * -1);

	CSoundMgr::Get_Instance()->PlayBGM(L"MainBGM.wav", 0.5f);
}

void CStage02::Update()
{
	KeyManager::Get_Instance()->Update_Key();

	if (!arrow)
	{
		arrow = new Arrow();
		arrow->initalize();
		arrow->setPosition(archer->getPosition());

		time = 1.5f;
	}

	archer->update();

	if (!arrow->isShot())
	{
		arrow->setDirection(archer->getDirection());
	}
	arrow->update();

	if (time >= 0.0f)
	{
		time -= Time.GetDeltaTime();
		return;
	}

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
	if (keyMgr->Key_Pressing(VK_TAB))
	{
		m_bReturn = true;
	}

	if (arrow && !arrow->isShot() && time <= 0.0f)
	{
		if (keyMgr->Key_Down(VK_LBUTTON))
		{
			soundMgr->StopSound(CHANNELID::SOUND_EFFECT);
			soundMgr->PlaySoundW(L"bow_pull.mp3",CHANNELID::SOUND_EFFECT, 1.f);
		}
		if (keyMgr->Key_Pressing(VK_LBUTTON))
		{
			if (power >= 500.0f)
				power = 500.0f;
			else
				power += Time.GetDeltaTime() * 200.0f;


		}
		else if (power >= 50.0f)
		{
			arrow->shoot(power);
			power = 0.0f;
			soundMgr->StopSound(CHANNELID::SOUND_EFFECT);
			soundMgr->PlaySoundW(L"bow_shot.mp3", CHANNELID::SOUND_EFFECT, 1.f);
		}
		else
		{
			power = 0.0f;
			soundMgr->StopSound(CHANNELID::SOUND_EFFECT);
		}
	}
	else if(arrow)
	{
		if (arrow->collision())
		{
			const D3DXVECTOR3* vertex = arrow->getVertex();
			DeadArrow* deadArrow = new DeadArrow();
			deadArrow->init(vertex[0], vertex[1]);
			deadArrows.push_back(deadArrow);
			soundMgr->PlaySoundW(L"arrow.mp3", CHANNELID::SOUND_EFFECT, 1.f);

			delete arrow;
			arrow = nullptr;
		}
	}

}

void CStage02::Render(HDC _hdc)
{

	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, groundBrush);
	HPEN oldPen = (HPEN)SelectObject(_hdc, groundPen);
	Rectangle(_hdc, 0, 500, 800, 600);

	SelectObject(_hdc, skyBrush);
	SelectObject(_hdc, skyPen);

	Rectangle(_hdc, 0, 0, 800, 500);

	SelectObject(_hdc, oldBrush);
	SelectObject(_hdc, oldPen);


	MoveToEx(_hdc, (int)(1000.0f - scrollMgr->Get_ScrollX()), 300, nullptr);
	LineTo(_hdc, (int)(1000.0f - scrollMgr->Get_ScrollX()), 530);


	archer->render(_hdc);
	if (arrow)
	{
		arrow->render(_hdc);
		if (!arrow->isShot() && time <= 0.0f)
		{
			std::wstringstream powerText;
			powerText << (int)(power / 5.0f) << " %";
			std::wstring gauge = powerText.str();

			D3DXVECTOR3 textPos = archer->getPosition();
			textPos.y -= 100.0f;
			TextOutW(_hdc, (int)textPos.x, (int)textPos.y, gauge.c_str(), gauge.length());
		}
	}

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

	soundMgr->StopAll();
}
