#include "stdafx.h"
#include "Ball.h"

#include "Pikachu.h"
#include "TimeManager.h"

Ball::Ball(Pikachu* p1, Pikachu* p2): mPlayer{p1, p2}, mWidth(0), mHeight(0)
{
}

void Ball::Initialize()
{
	mVelocity = { 0,0 };
	m_tInfo.vPos.x = 100.f;
	m_tInfo.vPos.y = 100.f;
	mWidth = 50.f;
	mHeight = 50.f;
}

void Ball::Update()
{
	float deltaTime = TimeManager::GetInstance().GetDeltaTime();
	mVelocity.y += 9.81f * deltaTime * 100.f;

	m_tInfo.vPos.x += mVelocity.x * deltaTime;
	m_tInfo.vPos.y += mVelocity.y * deltaTime;

	// 바운더리 밖으로 못 벗어나게 설정
	if (m_tInfo.vPos.y > WINCY - mHeight / 2.f)
	{
		m_tInfo.vPos.y = WINCY - mHeight / 2.f;
		mVelocity.y = -1000.f;
	}

	else if (m_tInfo.vPos.y < mHeight / 2.f)
	{
		m_tInfo.vPos.y = mHeight / 2.f;
		mVelocity.y *= -1.f;
	}

	if (m_tInfo.vPos.x < mWidth / 2.f)
	{
		m_tInfo.vPos.x = mWidth / 2.f;
		mVelocity.x *= -1.f;
	}

	else if (m_tInfo.vPos.x > WINCX - mWidth / 2.f)
	{
		m_tInfo.vPos.x = WINCX - mWidth / 2.f;
		mVelocity.x *= -1.f;
	}

	Collision();
}

void Ball::LateUpdate()
{

}

void Ball::Render(HDC hDC)
{
	Ellipse(hDC, m_tInfo.vPos.x - mWidth / 2.f, m_tInfo.vPos.y - mHeight / 2.f, m_tInfo.vPos.x + mWidth / 2.f, m_tInfo.vPos.y + mHeight / 2.f);
}

void Ball::Release()
{

}

void Ball::Collision()
{
	RECT temp;
	RECT p1 = { static_cast<LONG>(mPlayer[0]->GetLeftTop().x), static_cast<LONG>(mPlayer[0]->GetLeftTop().y), static_cast<LONG>(mPlayer[0]->GetRightBottom().x), static_cast<LONG>(mPlayer[0]->GetRightBottom().y) };
	RECT p2 = { static_cast<LONG>(mPlayer[1]->GetLeftTop().x), static_cast<LONG>(mPlayer[1]->GetLeftTop().y), static_cast<LONG>(mPlayer[1]->GetRightBottom().x), static_cast<LONG>(mPlayer[1]->GetRightBottom().y) };
	RECT ball = { static_cast<LONG>(m_tInfo.vPos.x - mWidth / 2.f), static_cast<LONG>(m_tInfo.vPos.y - mHeight / 2.f), static_cast<LONG>(m_tInfo.vPos.x + mWidth / 2.f), static_cast<LONG>(m_tInfo.vPos.y + mHeight / 2.f) };
	if (IntersectRect(&temp, &p1, &ball))
	{
		D3DXVECTOR3 dir = mPlayer[0]->Get_Info().vPos - m_tInfo.vPos;
		D3DXVec3Normalize(&dir, &dir);
		m_tInfo.vPos.y = mPlayer[0]->GetLeftTop().y - mHeight;
		mVelocity.x = -dir.x * 500.f;
		mVelocity.y = -dir.y * 1000.f;
	}
}
