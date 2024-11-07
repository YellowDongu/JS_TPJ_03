#include "stdafx.h"
#include "Pikachu.h"

#include <sstream>
#include <string>

#include "CBmpMgr.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "SoundMgr.h"

Pikachu::Pikachu(int type): mClip{}, mState(IDLE), mType(static_cast<PlayerType>(type)), mAngle(0), mWidth(0), mHeight(0),
                            mCurrentAniTime(0),
                            mFrame(0),
                            mScore(0),
                            mSliding(false), mSmash(false), mJump(false)
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

	switch (mType)
	{
	case PLAYER01:
		mClip[IDLE] = { CBmpMgr::Get_Instance()->Find_Image(L"Pikachu1P_Idle"), 128,128,5 };
		mClip[JUMP] = { CBmpMgr::Get_Instance()->Find_Image(L"Pikachu1P_Jump"), 128,128,5 };
		mClip[SLIDING] = { CBmpMgr::Get_Instance()->Find_Image(L"Pikachu_Sliding"), 128,128,2 };
		mClip[SLIDING_FLIP] = { CBmpMgr::Get_Instance()->Find_Image(L"Pikachu_Sliding_Flip"), 128,128,2 };
		mOffset = { -58.f,-25.f };
		break;
	case PLAYER02:
		mClip[IDLE] = { CBmpMgr::Get_Instance()->Find_Image(L"Pikachu2P_Idle"), 128,128,5 };
		mClip[JUMP] = { CBmpMgr::Get_Instance()->Find_Image(L"Pikachu2P_Jump"), 128,128,5 };
		mClip[SLIDING] = { CBmpMgr::Get_Instance()->Find_Image(L"Pikachu_Sliding"), 128,128,2 };
		mClip[SLIDING_FLIP] = { CBmpMgr::Get_Instance()->Find_Image(L"Pikachu_Sliding_Flip"), 128,128,2 };
		mOffset = { -18.f,-25.f };
		break;
	}

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
	D3DXVECTOR3 leftTop = GetLeftTop();
	int left = (int)(leftTop.x + mOffset.x);
	int top = (int)(leftTop.y + mOffset.y);

	// sprite render
	GdiTransparentBlt(hDC,
		left, top,
		128, 128,
		mClip[mState].Bitmap,
		128 * mFrame, 0,
		128, 128,
		RGB(127, 127, 127));


	switch (mType)
	{
	case PLAYER01:
		if (mScore < 10)
		{
			GdiTransparentBlt(hDC,
				100, 100,
				64, 64,
				CBmpMgr::Get_Instance()->Find_Image(L"Number"),
				64 * (mScore % 10), 0,
				64, 64,
				RGB(127, 127, 127));
		}

		else if (mScore >= 10)
		{
			GdiTransparentBlt(hDC,
				100, 100,
				64, 64,
				CBmpMgr::Get_Instance()->Find_Image(L"Number"),
				64 * (mScore / 10), 0,
				64, 64,
				RGB(127, 127, 127));

			GdiTransparentBlt(hDC,
				166, 100,
				64, 64,
				CBmpMgr::Get_Instance()->Find_Image(L"Number"),
				64 * (mScore % 10), 0,
				64, 64,
				RGB(127, 127, 127));
		}
		
		break;
	case PLAYER02:
		if (mScore < 10)
		{
			GdiTransparentBlt(hDC,
				700 - 64, 100,
				64, 64,
				CBmpMgr::Get_Instance()->Find_Image(L"Number"),
				64 * (mScore % 10), 0,
				64, 64,
				RGB(127, 127, 127));
		}

		else if (mScore >= 10)
		{
			GdiTransparentBlt(hDC,
				700 - 66 - 64, 100,
				64, 64,
				CBmpMgr::Get_Instance()->Find_Image(L"Number"),
				64 * (mScore / 10), 0,
				64, 64,
				RGB(127, 127, 127));

			GdiTransparentBlt(hDC,
				700 - 64, 100,
				64, 64,
				CBmpMgr::Get_Instance()->Find_Image(L"Number"),
				64 * (mScore % 10), 0,
				64, 64,
				RGB(127, 127, 127));
		}
		break;
	}


	UpdateAnimation();
}

void Pikachu::Release()
{
}

D3DXVECTOR3 Pikachu::GetLeftTop()
{
	float left = (std::min)({ mVertices[0].x,mVertices[1].x,mVertices[2].x ,mVertices[3].x });
	float top = (std::min)({ mVertices[0].y, mVertices[1].y,mVertices[2].y,mVertices[3].y });
	D3DXVECTOR3 leftTop = { left,top,0 };
	return leftTop;
}

D3DXVECTOR3 Pikachu::GetRightBottom()
{
	float right = (std::max)({ mVertices[0].x,mVertices[1].x,mVertices[2].x ,mVertices[3].x });
	float bottom = (std::max)({ mVertices[0].y, mVertices[1].y,mVertices[2].y,mVertices[3].y });
	D3DXVECTOR3 rightBottom = { right,bottom,0 };
	return rightBottom;
}

void Pikachu::StartGame()
{
	switch (mType)
	{
	case PLAYER01:
		mVelocity = { 0,0 };
		mAngle = 0;
		m_tInfo.vPos = { 100.f,500.f,0 };
		break;
	case PLAYER02:
		mVelocity = { 0,0 };
		mAngle = 0;
		m_tInfo.vPos = { 700.f,500.f,0 };
		break;
	}
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
		if (GetRightBottom().y > 524)
		{
			mState = IDLE;
			mVelocity.y = 0;
			mOffset = { -58.f,-25.f };
			mSliding = false;
			mSmash = false;
			mJump = false;
			mAngle = 0;
			m_tInfo.vPos.y = 524 - mHeight / 2.f;
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
		if (GetRightBottom().y > 524)
		{
			mState = IDLE;
			mVelocity.y = 0;
			mOffset = { -18.f,-25.f };
			mSliding = false;
			mSmash = false;
			mJump = false;
			mAngle = 0;
			m_tInfo.vPos.y = 524 - mHeight / 2.f;
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
			if (!mJump && KeyManager::Get_Instance()->Key_Pressing('Z'))
			{
				// 슬라이딩
				CSoundMgr::Get_Instance()->StopSound(SOUND_P1);
				CSoundMgr::Get_Instance()->PlaySoundW(L"Pikachu_Jump.wav", SOUND_P1, 0.5f);
				mState = SLIDING_FLIP;
				mSliding = true;
				mFrame = 0;
				mAngle = -90.f;
				mVelocity.x = -400.f;
				mVelocity.y = -250.f;
				mOffset = { 0,-68.f };
			}

			else
			{
				mVelocity.x = -250.f;
			}
		}

		else if (KeyManager::Get_Instance()->Key_Pressing('G') && !mSliding)
		{
			if (!mJump && KeyManager::Get_Instance()->Key_Pressing('Z'))
			{
				// 슬라이딩
				CSoundMgr::Get_Instance()->StopSound(SOUND_P1);
				CSoundMgr::Get_Instance()->PlaySoundW(L"Pikachu_Jump.wav", SOUND_P1, 0.5f);
				mSliding = true;
				mState = SLIDING;
				mFrame = 0;
				mAngle = 90.f;
				mVelocity.x = 400.f;
				mVelocity.y = -250.f;
				mOffset = { 0,-68.f };
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

		if (!mJump && KeyManager::Get_Instance()->Key_Pressing('R') && !mSliding)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_P1);
			CSoundMgr::Get_Instance()->PlaySoundW(L"Pikachu_Jump.wav", SOUND_P1, 0.5f);
			mJump = true;
			mState = JUMP;
			mVelocity.y = -500.f;
		}

		if (mJump && KeyManager::Get_Instance()->Key_Pressing('Z'))
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_P1);
			CSoundMgr::Get_Instance()->PlaySoundW(L"Pikachu_Smash.wav", SOUND_P1, 0.5f);
			mSmash = true;
		}

		if (mJump && KeyManager::Get_Instance()->Key_Up('Z'))
		{
			mSmash = false;
		}
		break;

	case PLAYER02:
		if (KeyManager::Get_Instance()->Key_Down(VK_LEFT) && !mSliding)
		{
			mVelocity.x = -250.f;
		}

		else if (KeyManager::Get_Instance()->Key_Down(VK_RIGHT) && !mSliding)
		{
			mVelocity.x = 250.f;
		}

		if (KeyManager::Get_Instance()->Key_Pressing(VK_LEFT) && !mSliding)
		{
			if (!mJump && KeyManager::Get_Instance()->Key_Pressing(VK_RETURN) && mVelocity.y == 0)
			{
				// 슬라이딩
				CSoundMgr::Get_Instance()->StopSound(SOUND_P2);
				CSoundMgr::Get_Instance()->PlaySoundW(L"Pikachu_Jump.wav", SOUND_P2, 0.5f);
				mState = SLIDING_FLIP;
				mSliding = true;
				mFrame = 0;
				mAngle = -90.f;
				mVelocity.x = -400.f;
				mVelocity.y = -250.f;
				mOffset = { 0,-68.f };
			}

			else
			{
				mVelocity.x = -250.f;
			}
		}

		else if (KeyManager::Get_Instance()->Key_Pressing(VK_RIGHT) && !mSliding)
		{
			if (!mJump && KeyManager::Get_Instance()->Key_Pressing(VK_RETURN) && mVelocity.y == 0)
			{
				// 슬라이딩
				CSoundMgr::Get_Instance()->StopSound(SOUND_P2);
				CSoundMgr::Get_Instance()->PlaySoundW(L"Pikachu_Jump.wav", SOUND_P2, 0.5f);
				mSliding = true;
				mState = SLIDING;
				mFrame = 0;
				mAngle = 90.f;
				mVelocity.x = 400.f;
				mVelocity.y = -250.f;
				mOffset = { 0,-68.f };
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

		if (!mJump && KeyManager::Get_Instance()->Key_Pressing(VK_UP) && !mSliding)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_P2);
			CSoundMgr::Get_Instance()->PlaySoundW(L"Pikachu_Jump.wav", SOUND_P2, 0.5f);
			mJump = true;
			mState = JUMP;
			mVelocity.y = -500.f;
		}

		if (mJump && KeyManager::Get_Instance()->Key_Pressing(VK_RETURN))
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_P2);
			CSoundMgr::Get_Instance()->PlaySoundW(L"Pikachu_Smash.wav", SOUND_P2, 0.5f);
			mSmash = true;
		}

		if (mJump && KeyManager::Get_Instance()->Key_Up(VK_RETURN))
		{
			mSmash = false;
		}

		break;
	}
}

void Pikachu::UpdateVertex()
{
	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(mAngle));

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

void Pikachu::UpdateAnimation()
{
	mCurrentAniTime += TimeManager::GetInstance().GetDeltaTime();
	if (mCurrentAniTime >= 0.15f)
	{
		mCurrentAniTime = 0;
		++mFrame;
		if (mFrame >= mClip[mState].Frame) mFrame = 0;
	}
}
