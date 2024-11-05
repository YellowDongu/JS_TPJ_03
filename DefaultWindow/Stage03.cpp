#include "stdafx.h"
#include "Stage03.h"


CStage03::CStage03() : m_pPlayer(nullptr), m_pShotPutBall(nullptr)
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

	dynamic_cast<CShotPutBall*>(m_pShotPutBall)->Set_Player(m_pPlayer);
}

void CStage03::Update()
{
	m_pPlayer->Update();
	m_pShotPutBall->Update();
}

void CStage03::LateUpdate()
{
}

void CStage03::Render(HDC _hdc)
{
	m_pPlayer->Render(m_DC);
	m_pShotPutBall->Render(m_DC);
}

void CStage03::Release()
{
	Safe_Delete<CObj*>(m_pPlayer);
	Safe_Delete<CObj*>(m_pShotPutBall);

	ReleaseDC(g_hWnd, m_DC);
}
