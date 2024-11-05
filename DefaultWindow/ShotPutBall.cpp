#include "stdafx.h"
#include "ShotPutBall.h"
#include "KeyManager.h"
#include "ShotPutPlayer.h"

CShotPutBall::CShotPutBall()
{
}

CShotPutBall::~CShotPutBall()
{
}

void CShotPutBall::Initialize()
{
}

void CShotPutBall::Update()
{
	m_tInfo.vPos = { m_pPlayer->Get_Info().vPos.x + cosf(D3DXToRadian(-(static_cast<CShotPutPlayer*>(m_pPlayer)->GetAngle()))) * 100.f,
				m_pPlayer->Get_Info().vPos.y + sinf(D3DXToRadian(-(static_cast<CShotPutPlayer*>(m_pPlayer)->GetAngle()))) * 100.f,
				0.f };

	if (/* 회전하는 키를 때면*/ false)
	{
		// 현재 m_tinfo.vpos에 오른쪽 뱡향 법선 벡터 방향으로 날아가게 한다.
		m_tInfo.vPos.x += cosf(D3DXToRadian(-(static_cast<CShotPutPlayer*>(m_pPlayer)->GetAngle() + 90.f))) * 10.f;
		m_tInfo.vPos.y -= sinf(D3DXToRadian(-(static_cast<CShotPutPlayer*>(m_pPlayer)->GetAngle() + 90.f))) * 10.f;
	}
}

void CShotPutBall::Render(HDC hDC)
{
	Ellipse(hDC, m_tInfo.vPos.x - 20, m_tInfo.vPos.y - 20, m_tInfo.vPos.x + 20, m_tInfo.vPos.y + 20);
}

void CShotPutBall::Release()
{
}
