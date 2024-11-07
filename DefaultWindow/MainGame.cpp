#include "stdafx.h"
#include "MainGame.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "CScrollMgr.h"

CMainGame::CMainGame() : m_DC(nullptr), m_hBit(nullptr), m_memDc(nullptr)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(g_hWnd);
	m_hBit = CreateCompatibleBitmap(m_DC, WINCX, WINCY);
	m_memDc = CreateCompatibleDC(m_DC);

	HBITMAP hPrevBit = static_cast<HBITMAP>(SelectObject(m_memDc, m_hBit));
	DeleteObject(hPrevBit);

	CSceneManager::Instantiate();

}

void CMainGame::Update()
{
	sceneMgr->Update();
	sceneMgr->LateUpdate();
}

void CMainGame::Render()
{
	Rectangle(m_memDc, 0, 0, WINCX, WINCY);
	sceneMgr->Render(m_memDc);
	BitBlt(m_DC, 0, 0, WINCX, WINCY, m_memDc, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{

	CSceneManager::Destroy();
	KeyManager::Get_Instance()->Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	ReleaseDC(g_hWnd, m_DC);
}
