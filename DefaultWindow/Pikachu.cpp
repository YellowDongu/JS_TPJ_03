#include "stdafx.h"
#include "Pikachu.h"

#include "KeyManager.h"
#include "TimeManager.h"

Pikachu::Pikachu(int type): mType(static_cast<PlayerType>(type)), mWidth(0), mHeight(0), mSliding(false)
{
}

void Pikachu::Initialize()
{
	if (mType == PLAYER01)
	{
		m_tInfo.vPos = { 100.f,500.f,0 };
	}

	else if (mType == PLAYER02)
	{
		m_tInfo.vPos = { 700.f,500.f,0 };
	}

	mVelocity = { 0,0 };
	mWidth = 50.f;
	mHeight = 100.f;

	float halfWidth = mWidth * 0.5f;
	float halfHeight = mHeight * 0.5f;

	mVertices[0] = { m_tInfo.vPos.x - halfWidth,m_tInfo.vPos.y - halfHeight, 0.f };
	mVertices[1] = { m_tInfo.vPos.x + halfWidth, m_tInfo.vPos.y -halfHeight, 0.f };  // 오른쪽 상단
	mVertices[2] = { m_tInfo.vPos.x + halfWidth, m_tInfo.vPos.y + halfHeight, 0.f };   // 오른쪽 하단
	mVertices[3] = { m_tInfo.vPos.x - halfWidth, m_tInfo.vPos.y + halfHeight, 0.f };   // 왼쪽 하단
}

void Pikachu::Update()
{
	Move();
}

void Pikachu::LateUpdate()
{
	HandleVelocityInput();
	UpdateVertex();
}

void Pikachu::Render(HDC hDC)
{
	MoveToEx(hDC, static_cast<int>(mVertices[0].x), static_cast<int>(mVertices[0].y), nullptr);
	LineTo(hDC, static_cast<int>(mVertices[1].x), static_cast<int>(mVertices[1].y));
	LineTo(hDC, static_cast<int>(mVertices[2].x), static_cast<int>(mVertices[2].y));
	LineTo(hDC, static_cast<int>(mVertices[3].x), static_cast<int>(mVertices[3].y));
	LineTo(hDC, static_cast<int>(mVertices[0].x), static_cast<int>(mVertices[0].y));
}

void Pikachu::Release()
{
}

void Pikachu::Move()
{
	float deltaTime = TimeManager::GetInstance().GetDeltaTime();
	mVelocity.y += 9.81f * deltaTime * 100.f;

	m_tInfo.vPos.x += mVelocity.x * deltaTime;
	m_tInfo.vPos.y += mVelocity.y * deltaTime;

	switch (mType)
	{
	case PLAYER01:
		// 바운더리 밖으로 못 벗어나게 설정
		if (m_tInfo.vPos.y > WINCY - mHeight / 2.f)
		{
			mSliding = false;
			m_tInfo.vPos.y = WINCY - mHeight / 2.f;
		}

		if (m_tInfo.vPos.x < mWidth / 2.f)
		{
			m_tInfo.vPos.x = mWidth / 2.f;
			mVelocity.x = 0;
		}

		else if (m_tInfo.vPos.x > WINCX / 2.f - mWidth / 2.f)
		{
			m_tInfo.vPos.x = WINCX / 2.f - mWidth / 2.f;
			mVelocity.x = 0;
		}
		break;

	case PLAYER02:
		// 바운더리 밖으로 못 벗어나게 설정
		if (m_tInfo.vPos.y > WINCY - mHeight / 2.f)
		{
			mSliding = false;
			m_tInfo.vPos.y = WINCY - mHeight / 2.f;
		}

		if (m_tInfo.vPos.x < WINCX / 2.f + mWidth / 2.f)
		{
			m_tInfo.vPos.x = WINCX / 2.f + mWidth / 2.f;
			mVelocity.x = 0;
		}

		else if (m_tInfo.vPos.x > WINCX - mWidth / 2.f)
		{
			m_tInfo.vPos.x = WINCX - mWidth / 2.f;
			mVelocity.x = 0;
		}
		break;
	}
}

void Pikachu::HandleVelocityInput()
{
	switch (mType)
	{
	case PLAYER01:
		if (KeyManager::Get_Instance()->Key_Down('D') && !mSliding)
		{
			mVelocity.x = -250.f;
		}

		else if (KeyManager::Get_Instance()->Key_Down('G') && !mSliding)
		{
			mVelocity.x = 250.f;
		}

		if (KeyManager::Get_Instance()->Key_Pressing('D') && !mSliding)
		{
			if (KeyManager::Get_Instance()->Key_Down('Z'))
			{
				// 슬라이딩
				mSliding = true;
				mVelocity.x = -400.f;
				mVelocity.y = -250.f;
			}

			else
			{
				mVelocity.x = -250.f;
			}
		}

		else if (KeyManager::Get_Instance()->Key_Pressing('G') && !mSliding)
		{
			if (KeyManager::Get_Instance()->Key_Down('Z'))
			{
				// 슬라이딩
				mSliding = true;
				mVelocity.x = 400.f;
				mVelocity.y = -250.f;
			}

			else
			{
				mVelocity.x = 250.f;
			}
		}

		else
		{
			if (!mSliding)
			{
				mVelocity.x = 0;
			}
		}

		if (KeyManager::Get_Instance()->Key_Down('R') && !mSliding)
		{
			mVelocity.y = -500.f;
		}
		break;

	case PLAYER02:
		if (KeyManager::Get_Instance()->Key_Down(VK_LEFT))
		{
			mVelocity.x = -250.f;
		}

		else if (KeyManager::Get_Instance()->Key_Down(VK_RIGHT))
		{
			mVelocity.x = 250.f;
		}

		if (KeyManager::Get_Instance()->Key_Pressing(VK_LEFT))
		{
			mVelocity.x = -250.f;
		}

		else if (KeyManager::Get_Instance()->Key_Pressing(VK_RIGHT))
		{
			mVelocity.x = 250.f;
		}

		else
		{
			mVelocity.x = 0;
		}

		if (KeyManager::Get_Instance()->Key_Down(VK_UP))
		{
			mVelocity.y = -500.f;
		}
		break;
	}
}

void Pikachu::UpdateVertex()
{
	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	if (mSliding)
	{
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(90.f));
	}
	else
	{
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0));
	}
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	float halfWidth = mWidth * 0.5f;
	float halfHeight = mHeight * 0.5f;

	// 회전 전 상대 좌표로 설정
	D3DXVECTOR3 localVertices[4] = {
		{ -halfWidth, -halfHeight, 0.f },  // 왼쪽 상단
		{ halfWidth, -halfHeight, 0.f },   // 오른쪽 상단
		{ halfWidth, halfHeight, 0.f },    // 오른쪽 하단
		{ -halfWidth, halfHeight, 0.f }    // 왼쪽 하단
	};

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&mVertices[i], &localVertices[i], &m_tInfo.matWorld);
	}
}
