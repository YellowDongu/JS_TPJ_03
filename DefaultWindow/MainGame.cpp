#include "stdafx.h"
#include "MainGame.h"
#include "SceneManager.h"
#include "KeyManager.h"

CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(g_hWnd);

	CSceneManager::Instantiate();

}

void CMainGame::Update()
{
	sceneMgr->Update();
	sceneMgr->LateUpdate();
}

void CMainGame::Render()
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	sceneMgr->Render(m_DC);

}

void CMainGame::Release()
{
	sceneMgr->Destroy();
	KeyManager::Get_Instance()->Destroy_Instance();
	ReleaseDC(g_hWnd, m_DC);
}
