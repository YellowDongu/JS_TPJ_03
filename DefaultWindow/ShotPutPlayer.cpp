#include "stdafx.h"
#include "ShotPutPlayer.h"
#include "KeyManager.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"

CShotPutPlayer::CShotPutPlayer() : m_fAngle(0.f), m_fXSacle(1.f), m_fYSacle(1.f), m_fPosinAngle(0.f), m_fRotSpeed(0.f), m_bIsRotEnd(false)
{
}

CShotPutPlayer::~CShotPutPlayer()
{
	Release();
}

void CShotPutPlayer::Initialize()
{
	// 아직 값 안채워넣음
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ShotPutPlayer.bmp", L"ShotPutPlayer");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ShotPutPlayer.bmp", L"ShotPutPlayerPlg");

	m_tInfo.vPos = { 100.f, 300.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	m_fSpeed = 3.f;
}

void CShotPutPlayer::Update()
{
	KeyInput();

	SetMatrix();
}

void CShotPutPlayer::LateUpdate()
{

}

void CShotPutPlayer::Render(HDC hDC)
{
	// 사각형의 꼭지점
	D3DXVECTOR3 vecVertx[4] = {
		   { -15.f,  15.f, 0.f },
		   { -15.f, -15.f, 0.f },
		   {  15.f, -15.f, 0.f },
		   {  15.f,  15.f, 0.f },
	};

	// 각 꼭지점에 회전 변환 적용
	for (int i = 0; i < 4; ++i)
	{
		// 행렬의 곱
		D3DXVec3TransformCoord(&vecVertx[i], &vecVertx[i], &m_tInfo.matWorld);
	}

	// 사각형 그리기
	//MoveToEx(hDC, vecVertx[0].x, vecVertx[0].y, nullptr);
	//for (int i = 1; i < 4; ++i)
	//{
	//	LineTo(hDC, vecVertx[i].x, vecVertx[i].y);
	//}
	//LineTo(hDC, vecVertx[0].x, vecVertx[0].y);

	POINT pt[4] = { {vecVertx[1].x, vecVertx[1].y}, {vecVertx[2].x, vecVertx[2].y}, {vecVertx[0].x, vecVertx[0].y}, {vecVertx[3].x, vecVertx[3].y} };

	HDC hPlgDC = CBmpMgr::Get_Instance()->Find_Image(L"ShotPutPlayerPlg");
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ShotPutPlayer");

	PlgBlt(hDC,
		pt,
		hMemDC,
		0,
		0,
		15,
		15,
		nullptr,
		0,
		0);

	// 포신
	D3DXVECTOR3 vecStart = m_tInfo.vPos;
	D3DXVECTOR3 vecEnd = {
		m_tInfo.vPos.x + cosf(D3DXToRadian(m_fAngle + m_fPosinAngle)) * 40.f * m_fXSacle,
		m_tInfo.vPos.y - sinf(D3DXToRadian(m_fAngle + m_fPosinAngle)) * 40.f * m_fYSacle,
		0.f
	};

	MoveToEx(hDC, vecStart.x, vecStart.y, nullptr);
	LineTo(hDC, vecEnd.x, vecEnd.y);
}

void CShotPutPlayer::Release()
{
}

void CShotPutPlayer::KeyInput()
{
	if (KeyManager::Get_Instance()->Key_Up(VK_RBUTTON))
	{
		m_bIsRotEnd = true;
	}

	if (KeyManager::Get_Instance()->Key_Pressing(VK_RBUTTON) && !m_bIsRotEnd)
	{
		if (m_fRotSpeed > 15.5f)
		{
			m_bIsRotEnd = true;
		}
		else
		{
			m_fRotSpeed += 0.03f;
			m_fAngle -= m_fRotSpeed;
			m_tInfo.vPos.x += m_fSpeed * 0.1f;
		}
	}
}

void CShotPutPlayer::SetMatrix()
{
	D3DXMatrixScaling(&matScale, m_fXSacle, m_fYSacle, 1.f); // 크기
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(-m_fAngle)); // 회전
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z); // 위치
	m_tInfo.matWorld = matScale * matRotZ * matTrans;
}

