#include "stdafx.h"
#include "Ball.h"

#include "AnimationCurve.h"
#include "CBmpMgr.h"
#include "Pikachu.h"
#include "TimeManager.h"

Ball::Ball(Pikachu* p1, Pikachu* p2): mFadeBitmap(nullptr), mPlayer{p1, p2}, mWidth(0), mHeight(0), mOpacity(0),
                                      mFadeIn(false),
                                      mFadeOut(false),
                                      mCurrentTime(0), mAniTime(0), mFrame(0)
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
	if (m_tInfo.vPos.y > 524 - mHeight / 2.f)
	{
		m_tInfo.vPos.y = 524 - mHeight / 2.f;
		TimeManager::GetInstance().SlowMotion(0.1f, 5.f);
		mFadeOut = true;
		mOpacity = 0.f;
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
	if (mFadeOut)
	{
		mCurrentTime += TimeManager::GetInstance().GetUnscaledDeltaTime();
		mOpacity = AnimationCurve::Lerp(0, 255, mCurrentTime / 1.0f);
		if (mCurrentTime >= 1.f)
		{
			// 다시 시작 로직
			if (m_tInfo.vPos.x < WINCX / 2.f)
			{
				mPlayer[1]->AddScore(1);
				m_tInfo.vPos = { 700.f,100.f,0 };
			}

			else if (m_tInfo.vPos.x > WINCX / 2.f)
			{
				mPlayer[0]->AddScore(1);
				m_tInfo.vPos = { 100.f,100.f,0 };
			}
			mVelocity = { 0,0 };
			mOpacity = 255;
			mCurrentTime = 0;
			mFadeIn = true;
			mFadeOut = false;
			for (auto& p : mPlayer)
			{
				p->StartGame();
			}
		}
	}

	if (mFadeIn)
	{
		mCurrentTime += TimeManager::GetInstance().GetUnscaledDeltaTime();
		mOpacity = AnimationCurve::Lerp(255, 0, mCurrentTime / .5f);
		if (mCurrentTime >= .5f)
		{
			mOpacity = 0;
			mCurrentTime = 0;
			mFadeIn = false;
			mFadeOut = false;
			TimeManager::GetInstance().SlowMotion(1.f, 0.f);
		}
	}


	mAniTime += TimeManager::GetInstance().GetDeltaTime();
	if (mAniTime >= 0.1f)
	{
		mAniTime = 0;
		++mFrame;
		if (mFrame == 5) mFrame = 0;
	}	
}

void Ball::Render(HDC hDC)
{
	// 524
	//Rectangle(hDC, WINCX / 2 - 10, WINCY - 250, WINCX / 2 + 10, WINCY);

	// Ball
	GdiTransparentBlt(hDC,
		m_tInfo.vPos.x - 40, m_tInfo.vPos.y - 40,
		80, 80,
		CBmpMgr::Get_Instance()->Find_Image(L"Ball"),
		(80 * mFrame), 0,
		80, 80,
		RGB(127, 127, 127));

	//Ellipse(hDC, m_tInfo.vPos.x - mWidth / 2.f, m_tInfo.vPos.y - mHeight / 2.f, m_tInfo.vPos.x + mWidth / 2.f, m_tInfo.vPos.y + mHeight / 2.f);

	// Shadow
	GdiTransparentBlt(hDC,
		m_tInfo.vPos.x - 32, 524 - 7,
		64, 14,
		CBmpMgr::Get_Instance()->Find_Image(L"Ball_Shadow"),
		0, 0,
		64, 14,
		RGB(127, 127, 127));


	// fadeInOut
	if (!mFadeBitmap) InitFadeBitmap(hDC);

	// BLENDFUNCTION 설정
	BLENDFUNCTION blendFunc = {};
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	blendFunc.SourceConstantAlpha = mOpacity; // 현재 불투명도 값 (0~255)
	blendFunc.AlphaFormat = 0;

	// 메모리 DC 생성 및 비트맵 선택
	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, mFadeBitmap);

	// AlphaBlend를 사용하여 반투명 검은색 비트맵을 출력
	AlphaBlend(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, WINCX, WINCY, blendFunc);

	// 메모리 DC 및 비트맵 정리
	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
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

		if (mPlayer[0]->IsSmash())
		{
			mVelocity.x = -vDir.x * 2000.f;
			mVelocity.y = -vDir.y * 200.f;
		}
		else
		{
			mVelocity.x = -vDir.x * 500.f;
			mVelocity.y = -vDir.y * 1000.f;
		}
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

		if (mPlayer[1]->IsSmash())
		{
			mVelocity.x = -vDir.x * 2000.f;
			mVelocity.y = -vDir.y * 200.f;
		}
		else
		{
			mVelocity.x = -vDir.x * 500.f;
			mVelocity.y = -vDir.y * 1000.f;
		}
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

void Ball::InitFadeBitmap(HDC hDC)
{
	if (mFadeBitmap) DeleteObject(mFadeBitmap);

	// 검은색 비트맵 생성
	HDC hMemDC = CreateCompatibleDC(hDC);
	mFadeBitmap = CreateCompatibleBitmap(hDC, WINCX, WINCY);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, mFadeBitmap);

	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	RECT rect = { 0, 0, WINCX, WINCY };
	FillRect(hMemDC, &rect, hBrush);

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hBrush);
	DeleteDC(hMemDC);
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
