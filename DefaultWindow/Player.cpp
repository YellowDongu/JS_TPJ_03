#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	
	m_fSpeed = 3.f;
}

void CPlayer::Update()
{
	m_tInfo.vDir = ::Get_Mouse() - m_tInfo.vPos;

	// float fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);
	// 
	// m_tInfo.vDir.x /= fLength;
	// m_tInfo.vDir.y /= fLength;
	// m_tInfo.vDir.z = 0.f;
	// 
	// float	fDot = m_tInfo.vDir.x * m_tInfo.vLook.x + m_tInfo.vDir.y * m_tInfo.vLook.y;

	// 단위 벡터를 만들어주는 함수(단위 벡터의 결과를 저장할 벡터, 단위 벡터로 변환 시킬 벡터)
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	// 벡터의 크기를 계산하는 함수
	// float fLength = D3DXVec3Length(&m_tInfo.vDir);

	// 두 방향 벡터의 내적을 수행하는 함수
	float	fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	// 두 방향 벡터의 외적을 수행하는 함수
	// D3DXVec3Cross(결과를 저장할 벡터의 주소 ,방향 벡터 1의 주소, 방향 벡터 2의 주소)

	float	fAngle = acosf(fDot);

	if (m_tInfo.vPos.y < Get_Mouse().y)
		fAngle = 2.f * D3DX_PI - fAngle;

	m_tInfo.vPos.x += cosf(fAngle) * m_fSpeed;
	m_tInfo.vPos.y -= sinf(fAngle) * m_fSpeed;

	
}

void CPlayer::LateUpdate()
{
	D3DXMATRIX		matScale, matRotZ, matTrans;
		
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(45.f));
	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;
}

void CPlayer::Render(HDC hDC)
{
	
}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{
	
}


// 항등 행렬 만들기 함수
// D3DXMatrixIdentity(&항등 행렬을 만들어줄 행렬의 주소);

// 크기 변환 행렬 만들기 함수
// D3DXMatrixScaling(결과 값을 저장할 행렬의 주소, x배율, y배율, z배율)

// 회전 변환 행렬 만들기 함수
// D3DXMatrixRotationZ(결과 값을 저장할 행렬의 주소, 회전 각도(라디안))

// 위치 변환 행렬 만들기 함수
// D3DXMatrixTranslation(결과 값을 저장할 행렬의 주소, x, y, z 좌표)

// 벡터와 행렬의 곱셈 함수

// D3DXVec3TransformCoord(결과 벡터, 위치 벡터, 행렬)
// D3DXVec3TransformNormal(결과 벡터, 방향 벡터, 행렬)