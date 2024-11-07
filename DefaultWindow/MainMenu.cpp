#include "stdafx.h"
#include "MainMenu.h"
#include "KeyManager.h"
#include "CBmpMgr.h"
#include "SoundMgr.h"

#define bmpMgr CBmpMgr::Get_Instance()
#define keyMgr KeyManager::Get_Instance()

CMainMenu::CMainMenu()
{
}

CMainMenu::~CMainMenu()
{
}

void CMainMenu::Initialize()
{
	m_iOtherStage = -1;
	GameSelectButton* newButton = new GameSelectButton();
	buttons.push_back(newButton);
	newButton->init(RECT{ 185, 389, 285, 489 });
	newButton = new GameSelectButton();
	buttons.push_back(newButton);
	newButton->init(RECT{ 350, 388, 450, 488 });
	newButton = new GameSelectButton();
	buttons.push_back(newButton);
	newButton->init(RECT{ 523, 388, 623, 488 });
	bmpMgr->Insert_Bmp(L".\\Sprite\\MainMenu.bmp", L"MainMenu");
	CSoundMgr::Get_Instance()->PlayBGM(L"MainBGM.wav", 0.5f);

}

void CMainMenu::Update()
{
	keyMgr->Update_Key();

	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(g_hWnd, &mousePos);

	for (int i = 0; i < 3; i++)
	{
		if (!PtInRect(&buttons[i]->buttonArea(), mousePos))
			continue;
		if (buttons[i]->hoveringMouse())
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
	BitBlt(_hdc, 0,0,800,600, bmpMgr->Find_Image(L"MainMenu"), 0,0, SRCCOPY);


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
	CSoundMgr::Get_Instance()->StopAll();
}

