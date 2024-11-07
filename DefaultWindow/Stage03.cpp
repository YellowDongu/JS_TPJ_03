#include "stdafx.h"
#include "Stage03.h"
#include "KeyManager.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "SoundMgr.h"

CStage03::CStage03() : m_pPlayer(nullptr), m_pShotPutBall(nullptr), m_pShotPutStadium(nullptr)
{
}

CStage03::~CStage03()
{
}

void CStage03::Initialize()
{
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

	CSoundMgr::Get_Instance()->PlayBGM(L"MainBGM.wav", 1.f);
}

void CStage03::Update()
{
	m_pShotPutStadium->Update();
	m_pPlayer->Update();
	m_pShotPutBall->Update();
}

void CStage03::LateUpdate()
{

	m_pShotPutStadium->LateUpdate();
	m_pPlayer->LateUpdate();
	m_pShotPutBall->LateUpdate();

	Key_Input();

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
	CSoundMgr::Get_Instance()->StopAll();
	Safe_Delete<CObj*>(m_pPlayer);
	Safe_Delete<CObj*>(m_pShotPutBall);
	Safe_Delete<CObj*>(m_pShotPutStadium);
	CBmpMgr::Get_Instance()->Release();
}

void CStage03::Key_Input()
{
	if (KeyManager::Get_Instance()->Key_Up(VK_TAB))
	{
		m_bReturn = true;
	}

	if (KeyManager::Get_Instance()->Key_Down('R'))
	{
		Release();
		Initialize();
	}
}
