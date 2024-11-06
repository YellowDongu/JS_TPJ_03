#include "stdafx.h"
#include "ShotPutPlayer.h"
#include "KeyManager.h"

CShotPutPlayer::CShotPutPlayer() : m_fAngle(0.f), m_fXSacle(1.f), m_fYSacle(1.f), m_fPosinAngle(0.f), m_fRotSpeed(0.f)
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

void CShotPutPlayer::Render(HDC hDC)
{
	// �簢���� ������
	D3DXVECTOR3 vecVertx[4] = {
		   { -50.f,  50.f, 0.f },
		   { -50.f, -50.f, 0.f },
		   {  50.f, -50.f, 0.f },
		   {  50.f,  50.f, 0.f },
	};

	// �� �������� ȸ�� ��ȯ ����
	for (int i = 0; i < 4; ++i)
	{
		// ����� ��
		D3DXVec3TransformCoord(&vecVertx[i], &vecVertx[i], &m_tInfo.matWorld);
	}

	// �簢�� �׸���
	MoveToEx(hDC, vecVertx[0].x, vecVertx[0].y, nullptr);
	for (int i = 1; i < 4; ++i)
	{
		LineTo(hDC, vecVertx[i].x, vecVertx[i].y);
	}
	LineTo(hDC, vecVertx[0].x, vecVertx[0].y);


	// ����
	D3DXVECTOR3 vecStart = m_tInfo.vPos;
	D3DXVECTOR3 vecEnd = {
		m_tInfo.vPos.x + cosf(D3DXToRadian(m_fAngle + m_fPosinAngle)) * 100.f * m_fXSacle,
		m_tInfo.vPos.y - sinf(D3DXToRadian(m_fAngle + m_fPosinAngle)) * 100.f * m_fYSacle,
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
	if (KeyManager::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		if (m_fRotSpeed > 15.5f)
		{
			// �� ������!
			// ���� ��ü�� ���� ������ �� ��ǥ���� ���� ���͸� ���ϰ� �� ���͸� ���� ���ͷ� �̿��Ͽ�
			// ���� ������ ���� ���ǵ�� �����̼� ���ǵ忡 ����ϰ� �����
			// ���ư��� ���ǵ忡 ����Ͽ� ���� Ŀ���ٰ� �۾����� ������� �۾�����
			// ���������� ��ǥ ����
			// �÷��̾���� �Ÿ��� ����Ͽ� ���� �󸶳� �ָ������� ���
			// ���ھ ȭ�鿡 ����ؼ� �׵��� ���� ���߿� �ִ� �Ÿ��� ���
			// ���� ���� ������ ���ھ ȭ�� ���߾ӿ� ����ϰ�
			// ���� �ڿ� �ٽ� ������ ���ְ� ������ֱ�

			// ��Ʈ���� �����ε�
			// ������ �������� �ϰ��ִµ� �ű�ٰ� ��Ʈ���� ��� �׷�����? ����
			// �𸣰ڴ� ����
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
	D3DXMatrixScaling(&matScale, m_fXSacle, m_fYSacle, 1.f); // ũ��
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(-m_fAngle)); // ȸ��
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z); // ��ġ
	m_tInfo.matWorld = matScale * matRotZ * matTrans;
}

void CShotPutPlayer::LateUpdate()
{
}
