#include "stdafx.h"
#include "MainMenu.h"
#include "InputManager.h"

CMainMenu::CMainMenu()
{
}

CMainMenu::~CMainMenu()
{
}

void CMainMenu::Initialize()
{
	m_iOtherStage = -1;
	Input->Init(g_hWnd);
}

void CMainMenu::Update()
{
	if (false)
	{
		m_iOtherStage = 1;
	}
	if (false)
	{
		m_iOtherStage = 2;
	}
	if (false)
	{
		m_iOtherStage = 3;
	}
}

void CMainMenu::LateUpdate()
{


}

void CMainMenu::Render(HDC _hdc)
{



}

void CMainMenu::Release()
{
}

