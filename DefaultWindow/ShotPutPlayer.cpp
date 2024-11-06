#include "stdafx.h"
#include "ShotPutPlayer.h"
#include "KeyManager.h"
#include "CScrollMgr.h"

CShotPutPlayer::CShotPutPlayer() : m_fAngle(0.f), m_fXSacle(1.f), m_fYSacle(1.f), m_fPosinAngle(0.f), m_fRotSpeed(0.f), m_bIsRot(false)
{
}

CShotPutPlayer::~CShotPutPlayer()
{
	Release();
}

void CShotPutPlayer::Initialize()
{
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
	MoveToEx(hDC, vecVertx[0].x, vecVertx[0].y, nullptr);
	for (int i = 1; i < 4; ++i)
	{
		LineTo(hDC, vecVertx[i].x, vecVertx[i].y);
	}
	LineTo(hDC, vecVertx[0].x, vecVertx[0].y);


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
		m_bIsRot = true;
		// 던지기
	}

	if (KeyManager::Get_Instance()->Key_Pressing(VK_RBUTTON) && !m_bIsRot)
	{
		if (m_fRotSpeed > 15.5f)
		{
			// 공 던지기!
			// 공은 객체로 만들어서 포신의 끝 좌표에서 법선 벡터를 구하고 그 벡터를 방향 벡터로 이용하여
			// 공을 던지고 공의 스피드는 로테이션 스피드에 비례하게 만들고
			// 날아가는 스피드에 비례하여 공이 커병鳴 작아지고 어느정도 작아지면
			// 착지했으니 좌표 고정
			// 플레이어와의 거리를 계산하여 공이 얼마나 멀리갔는지 계산
			// 스코어를 화면에 출력해서 그동안 던진 공중에 최대 거리를 출력
			// 공이 땅에 닿으면 스코어를 화면 정중앙에 출력하고
			// 몇초 뒤에 다시 공던질 수있게 만들어주기

			// 비트맵이 문제인데
			// 라인투 무브투로 하고있는데 거기다가 비트맵을 어떻게 그려넣지? ㅋㅋ
			// 모르겠다 ㅋㅋ
			m_bIsRot = true;
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

