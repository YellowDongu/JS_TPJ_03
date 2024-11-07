#include "stdafx.h"
#include "ShotPutBall.h"
#include "KeyManager.h"
#include "ShotPutPlayer.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"
#include "SoundMgr.h"

float CShotPutBall::m_fBestScore = 0.f;

CShotPutBall::CShotPutBall() : m_fXScale(0.f), m_fYScale(0.f), m_pPlayer(nullptr), m_fSpeedCrashBoundary(0.f), m_bIsStop(false),
m_fCurScore(0.f)
{
	ZeroMemory(&m_vUpLine, sizeof(D3DXVECTOR3) * 2);
	ZeroMemory(&m_vDownLine, sizeof(D3DXVECTOR3) * 2);
}

CShotPutBall::~CShotPutBall()
{
	Release();
}

void CShotPutBall::Initialize()
{
	m_fSpeed = 10.f;

	m_fXScale = 1.f;
	m_fYScale = 1.f;

	m_vUpLine[0] = { 220.f, 250.f, 0.f }; // LeftTop
	m_vUpLine[1] = { 800.f, 0.f, 0.f }; // RightBottom

	m_vDownLine[0] = { 220.f, 350.f, 0.f }; // LeftTop
	m_vDownLine[1] = { 800.f, 600.f, 0.f }; // RightBottom
}

void CShotPutBall::Update()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"", L"");

	ScoreCal();
}

void CShotPutBall::LateUpdate()
{
	if (static_cast<CShotPutPlayer*>(m_pPlayer)->GetIsRotEnd())
	{
		// 현재 m_tinfo.vpos에 오른쪽 향 법선 벡터 방향으로 날아가게 한다.
		m_tInfo.vPos.x += cosf(D3DXToRadian((static_cast<CShotPutPlayer*>(m_pPlayer)->GetAngle() - 90.f))) * m_fSpeed;
		m_tInfo.vPos.y -= sinf(D3DXToRadian((static_cast<CShotPutPlayer*>(m_pPlayer)->GetAngle() - 90.f))) * m_fSpeed;
	}

	if (!static_cast<CShotPutPlayer*>(m_pPlayer)->GetIsRotEnd())
	{
		m_fSpeed = static_cast<CShotPutPlayer*>(m_pPlayer)->GetRotSpeed() * 0.8f;

		m_fSpeedCrashBoundary = m_fSpeed / 2.0f;

		m_tInfo.vPos = { m_pPlayer->Get_Info().vPos.x + cosf(D3DXToRadian(-(static_cast<CShotPutPlayer*>(m_pPlayer)->GetAngle()))) * 40.f,
			m_pPlayer->Get_Info().vPos.y + sinf(D3DXToRadian(-(static_cast<CShotPutPlayer*>(m_pPlayer)->GetAngle()))) * 40.f,
			0.f };
	}

	SetMatrix();
}

void CShotPutBall::Render(HDC hDC)
{
	D3DXVECTOR3 vecVertx[2] = {
		   { -7.f,  -7.f, 0.f }, // LeftTop
		   { 7.f, 7.f, 0.f }, // RightBottom
	};



	for (int i = 0; i < 2; ++i)
	{
		D3DXVec3TransformCoord(&vecVertx[i], &vecVertx[i], &m_tInfo.matWorld);
	}
	
	HBRUSH hNewBrush = CreateSolidBrush(RGB(0x00, 0x00, 0xff));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

	Ellipse(hDC, vecVertx[0].x, vecVertx[0].y, vecVertx[1].x, vecVertx[1].y);

	SelectObject(hDC, hOldBrush); // 기존에 사용하던것(Newpen)을 리턴함  
	DeleteObject(hNewBrush);


	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	// 스코어 출력
	TCHAR szBestScore[64] = L"";
	swprintf_s(szBestScore, L"Best Score : %.2f m", m_fBestScore);
	TextOut(hDC, 1, 1, szBestScore, wcslen(szBestScore));


	TCHAR szCurScore[64] = L"";
	swprintf_s(szCurScore, L"Current Score : %.2f m", m_fCurScore);
	TextOut(hDC, 1, 16, szCurScore, wcslen(szCurScore));
}

void CShotPutBall::Release()
{
}

void CShotPutBall::SetMatrix()
{
	D3DXMATRIX matScale, matRot ,matTrans;
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	D3DXMatrixScaling(&matScale, m_fXScale, m_fYScale, 0.f);
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(0));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRot * matTrans;
}

void CShotPutBall::ScoreCal()
{
	if (m_fSpeed > 0.0f)
	{
		m_fSpeed -= 0.1f;
		if (m_fSpeed < 0.0f)
		{
			m_fSpeed = 0.0f;
		}
	}

	if (static_cast<CShotPutPlayer*>(m_pPlayer)->GetIsRotEnd())
	{
		if (m_fSpeed > m_fSpeedCrashBoundary)
		{
			m_fXScale += 0.1f;
			m_fYScale += 0.1f;
		}
		else if (m_fSpeed > 0.0f)
		{
			m_fXScale -= 0.1f;
			m_fYScale -= 0.1f;
			if (m_fXScale < 1.0f)
			{
				m_fXScale = 1.0f;

			}
			if (m_fYScale < 1.0f)
			{
				m_fYScale = 1.0f;
			}
		}
		else if (m_fSpeed <= 0.0f)
		{
			m_bIsStop = true;
		}
	}

	m_fCurScore = sqrtf(powf(m_pPlayer->Get_Info().vPos.x - m_tInfo.vPos.x, 2) + powf(m_pPlayer->Get_Info().vPos.y - m_tInfo.vPos.y, 2));

	// 위쪽 선보다 위쪽에 있으면
	if (IsPointInLine(m_vUpLine[0], m_vUpLine[1]) == LINESTATE::UP)
		m_fCurScore = 0.f;

	// 아래쪽 선보다 아래에 있으면
	if (IsPointInLine(m_vDownLine[0], m_vDownLine[1]) == LINESTATE::DOWN)
		m_fCurScore = 0.f;

	if (m_tInfo.vPos.x < 255.f)
		m_fCurScore = 0.f;

	if (m_fBestScore < m_fCurScore && m_bIsStop)
	{
		CSoundMgr::Get_Instance()->StopAll();
		CSoundMgr::Get_Instance()->PlaySound(L"BestScore.wav", CHANNELID::SOUND_EFFECT, 1.f);
		m_fBestScore = m_fCurScore;
	}
		
}

int CShotPutBall::IsPointInLine(D3DXVECTOR3 _vecStartPoint, D3DXVECTOR3 _vecEndPoint)
{
	const float a = _vecEndPoint.y - _vecStartPoint.y;
	const float b = _vecStartPoint.x - _vecEndPoint.x;
	const float c = _vecEndPoint.x * _vecStartPoint.y - _vecStartPoint.x * _vecEndPoint.y;

	if(a* m_tInfo.vPos.x + b * m_tInfo.vPos.y + c > 0)
		return LINESTATE::UP;

	if (a * m_tInfo.vPos.x + b * m_tInfo.vPos.y + c < 0)
		return LINESTATE::DOWN;

	return LINESTATE::END;
}
