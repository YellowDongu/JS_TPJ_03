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

	// ���� ���͸� ������ִ� �Լ�(���� ������ ����� ������ ����, ���� ���ͷ� ��ȯ ��ų ����)
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	// ������ ũ�⸦ ����ϴ� �Լ�
	// float fLength = D3DXVec3Length(&m_tInfo.vDir);

	// �� ���� ������ ������ �����ϴ� �Լ�
	float	fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	// �� ���� ������ ������ �����ϴ� �Լ�
	// D3DXVec3Cross(����� ������ ������ �ּ� ,���� ���� 1�� �ּ�, ���� ���� 2�� �ּ�)

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


// �׵� ��� ����� �Լ�
// D3DXMatrixIdentity(&�׵� ����� ������� ����� �ּ�);

// ũ�� ��ȯ ��� ����� �Լ�
// D3DXMatrixScaling(��� ���� ������ ����� �ּ�, x����, y����, z����)

// ȸ�� ��ȯ ��� ����� �Լ�
// D3DXMatrixRotationZ(��� ���� ������ ����� �ּ�, ȸ�� ����(����))

// ��ġ ��ȯ ��� ����� �Լ�
// D3DXMatrixTranslation(��� ���� ������ ����� �ּ�, x, y, z ��ǥ)

// ���Ϳ� ����� ���� �Լ�

// D3DXVec3TransformCoord(��� ����, ��ġ ����, ���)
// D3DXVec3TransformNormal(��� ����, ���� ����, ���)