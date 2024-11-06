#include "stdafx.h"
#include "ShotPutBall.h"
#include "KeyManager.h"
#include "ShotPutPlayer.h"
#include "CScrollMgr.h"

CShotPutBall::CShotPutBall() : m_fXScale(0.f), m_fYScale(0.f), m_pPlayer(nullptr), m_fSpeedCrashBoundary(0.f)
{
}

CShotPutBall::~CShotPutBall()
{
}

void CShotPutBall::Initialize()
{
	m_fSpeed = 10.f;

	m_fXScale = 1.f;
	m_fYScale = 1.f;
}

void CShotPutBall::Update()
{
	if (m_fSpeed > 0.0f)
	{
		m_fSpeed -= 0.1f;
		if (m_fSpeed < 0.0f)
		{
			m_fSpeed = 0.0f;
		}
	}

	if (static_cast<CShotPutPlayer*>(m_pPlayer)->GetIsRot())
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
	}
	
}

void CShotPutBall::LateUpdate()
{
	if (static_cast<CShotPutPlayer*>(m_pPlayer)->GetIsRot())
	{
		// 현재 m_tinfo.vpos에 오른쪽 향 법선 벡터 방향으로 날아가게 한다.
		m_tInfo.vPos.x += cosf(D3DXToRadian((static_cast<CShotPutPlayer*>(m_pPlayer)->GetAngle() - 90.f))) * m_fSpeed;
		m_tInfo.vPos.y -= sinf(D3DXToRadian((static_cast<CShotPutPlayer*>(m_pPlayer)->GetAngle() - 90.f))) * m_fSpeed;
	}

	if (!static_cast<CShotPutPlayer*>(m_pPlayer)->GetIsRot())
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
	
	Ellipse(hDC, vecVertx[0].x, vecVertx[0].y, vecVertx[1].x, vecVertx[1].y);
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
