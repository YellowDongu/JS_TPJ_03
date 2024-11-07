#include "stdafx.h"
#include "Stage03.h"
#include "KeyManager.h"

CStage03::CStage03() : m_pPlayer(nullptr), m_pShotPutBall(nullptr), m_pShotPutStadium(nullptr)
{
}

CStage03::~CStage03()
{
}

void CStage03::Initialize()
{
	m_DC = GetDC(g_hWnd);

	if (!m_pPlayer)
	{
		m_pPlayer = new CShotPutPlayer;
		m_pPlayer->Initialize();
	}

	if (!m_pShotPutBall)
	{
		m_pShotPutBall = new CShotPutBall;
		m_pShotPutBall->Initialize();
	}

	if (!m_pShotPutStadium)
	{
		m_pShotPutStadium = new CShotPutStadium;
		m_pShotPutStadium->Initialize();
	}

	dynamic_cast<CShotPutBall*>(m_pShotPutBall)->Set_Player(m_pPlayer);
}

void CStage03::Update()
{
	m_pShotPutStadium->Update();
	m_pPlayer->Update();
	m_pShotPutBall->Update();
}

void CStage03::LateUpdate()
{
	if (KeyManager::Get_Instance()->Key_Up(VK_RETURN))
	{
		m_bReturn = true;
	}
	m_pShotPutStadium->LateUpdate();
	m_pPlayer->LateUpdate();
	m_pShotPutBall->LateUpdate();

	KeyManager::Get_Instance()->Update_Key();
}

void CStage03::Render(HDC _hdc)
{
	m_pShotPutStadium->Render(_hdc);
	m_pPlayer->Render(_hdc);
	m_pShotPutBall->Render(_hdc);
}

void CStage03::Release()
{
	Safe_Delete<CObj*>(m_pPlayer);
	Safe_Delete<CObj*>(m_pShotPutBall);
	Safe_Delete<CObj*>(m_pShotPutStadium);

	//ReleaseDC(g_hWnd, m_DC);
}
