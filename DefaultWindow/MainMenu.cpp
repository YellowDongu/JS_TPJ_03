#include "stdafx.h"
#include "MainMenu.h"
#include "KeyManager.h"

CMainMenu::CMainMenu()
{
}

CMainMenu::~CMainMenu()
{
}

void CMainMenu::Initialize()
{
	m_iOtherStage = -1;
	RECT rect = { 200, 300, 300, 400 };
	GameSelectButton* newButton = new GameSelectButton();
	buttons.push_back(newButton);
	newButton->init(rect, 1);
	newButton = new GameSelectButton();
	buttons.push_back(newButton);
	rect = { 350, 300, 450, 400 };
	newButton->init(rect, 2);
	newButton = new GameSelectButton();
	buttons.push_back(newButton);
	rect = { 500, 300, 600, 400 };
	newButton->init(rect, 3);
}

void CMainMenu::Update()
{

	if (!KeyManager::Get_Instance()->Key_Down(VK_LBUTTON)) return;

	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(g_hWnd, &mousePos);

	for (int i = 0; i < 3; i++)
	{
		if (PtInRect(&buttons[i]->buttonArea(), mousePos))
		{
			m_iOtherStage = i + 1;
		}
	}

}

void CMainMenu::LateUpdate()
{


}

void CMainMenu::Render(HDC _hdc)
{
	for (auto& button : buttons)
	{
		button->render(_hdc);
	}


}

void CMainMenu::Release()
{
	for (auto& button : buttons)
	{
		delete button;
	}
	buttons.clear();
}

