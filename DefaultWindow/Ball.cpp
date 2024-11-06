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

	mPrevPosition = m_tInfo.vPos;
}

void Ball::LateUpdate()
{
	Collision();
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
	RECT net = { WINCX / 2 - 10, WINCY - 250, WINCX / 2 + 10, WINCY };
	RECT ball = { static_cast<LONG>(m_tInfo.vPos.x - mWidth / 2.f), static_cast<LONG>(m_tInfo.vPos.y - mHeight / 2.f), static_cast<LONG>(m_tInfo.vPos.x + mWidth / 2.f), static_cast<LONG>(m_tInfo.vPos.y + mHeight / 2.f) };
	if (IntersectRect(&temp, &p1, &ball))
	{
		CollisionDirection dir = DetectBoxCollisionDir(ball, p1);

		D3DXVECTOR3 vDir = mPlayer[0]->Get_Info().vPos - m_tInfo.vPos;
		D3DXVec3Normalize(&vDir, &vDir);
		if (dir & TOP)
		{
			m_tInfo.vPos.y = mPlayer[0]->GetLeftTop().y - mHeight;
		}

		else if (dir & LEFT)
		{
			m_tInfo.vPos.x = mPlayer[0]->GetLeftTop().x - mWidth / 2;
		}

		else if (dir& RIGHT)
		{
			m_tInfo.vPos.x = mPlayer[0]->GetRightBottom().x + mWidth / 2;
		}


		mVelocity.x = -vDir.x * 500.f;
		mVelocity.y = -vDir.y * 1000.f;
	}

	if (IntersectRect(&temp, &p2, &ball))
	{
		CollisionDirection dir = DetectBoxCollisionDir(ball, p2);

		D3DXVECTOR3 vDir = mPlayer[1]->Get_Info().vPos - m_tInfo.vPos;
		D3DXVec3Normalize(&vDir, &vDir);
		if (dir & TOP)
		{
			m_tInfo.vPos.y = mPlayer[1]->GetLeftTop().y - mHeight;
		}

		else if (dir & LEFT)
		{
			m_tInfo.vPos.x = mPlayer[1]->GetLeftTop().x - mWidth /2 ;
		}

		else if (dir & RIGHT)
		{
			m_tInfo.vPos.x = mPlayer[1]->GetRightBottom().x + mWidth/2;
		}


		mVelocity.x = -vDir.x * 500.f;
		mVelocity.y = -vDir.y * 1000.f;
	}

	if (IntersectRect(&temp, &net, &ball))
	{
		CollisionDirection dir = DetectBoxCollisionDir(ball, net);

		if (dir & TOP)
		{
			mVelocity.y *= -1.f;
			m_tInfo.vPos.y = (int)(net.top - mHeight / 2.f);
		}

		else if (dir & LEFT)
		{
			mVelocity.x *= -1.f;
			m_tInfo.vPos.x = (int)(net.left - mWidth / 2.f);
		}

		else if (dir & RIGHT)
		{
			mVelocity.x *= -1.f;
			m_tInfo.vPos.x = (int)(net.right + mWidth / 2.f);
		}
	}
}

CollisionDirection Ball::DetectBoxCollisionDir(const RECT& objRect, const RECT& otherRect)
{
	CollisionDirection collisionDir = NONE;

	int overlapLeft = objRect.right - otherRect.left;
	int overlapRight = otherRect.right - objRect.left;
	int overlapTop = objRect.bottom - otherRect.top;
	int overlapBottom = otherRect.bottom - objRect.top;

	int minOverlap = (std::min)({ overlapLeft,overlapRight,overlapTop,overlapBottom });

	// obj가 other의 왼쪽에서 충돌
	if (minOverlap == overlapLeft)
	{
		collisionDir = static_cast<CollisionDirection>(collisionDir | LEFT);
	}

	// obj가 other의 오른쪽에서 충돌
	else if (minOverlap == overlapRight)
	{
		collisionDir = static_cast<CollisionDirection>(collisionDir | RIGHT);
	}

	// obj가 other의 위에서 충돌
	if (minOverlap == overlapTop)
	{
		collisionDir = static_cast<CollisionDirection>(collisionDir | TOP);
	}

	// obj가 other의 아래에서 충돌
	else if (minOverlap == overlapBottom)
	{
		collisionDir = static_cast<CollisionDirection>(collisionDir | BOTTOM);
	}

	return collisionDir;
}
