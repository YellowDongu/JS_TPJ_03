#include "stdafx.h"
#include "MainGame.h"
#include "SceneManager.h"

CMainGame::CMainGame() : m_pPlayer(nullptr)
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



	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Initialize();
	}

	if (!m_pMonster)
	{
		m_pMonster = new CMonster;
		m_pMonster->Initialize();
	}

	dynamic_cast<CMonster*>(m_pMonster)->Set_Player(m_pPlayer);
}

void CMainGame::Update()
{
	sceneMgr->Update();

	m_pPlayer->Update();
	m_pMonster->Update();
}

void CMainGame::Render()
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	sceneMgr->Render(m_DC);

	m_pPlayer->Render(m_DC);
	m_pMonster->Render(m_DC);
}

void CMainGame::Release()
{
	sceneMgr->Destroy();

	Safe_Delete<CObj*>(m_pPlayer);
	Safe_Delete<CObj*>(m_pMonster);

	ReleaseDC(g_hWnd, m_DC);
}
