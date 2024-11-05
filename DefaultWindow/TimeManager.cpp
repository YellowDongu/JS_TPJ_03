#include "stdafx.h"
#include "TimeManager.h"
#include <thread>

using namespace std::chrono;

TimeManager::TimeManager() : mFrequency(), mLastFrameTime(), mCurrentFrameTime(), mDeltaTime(0), mUnscaledDeltaTime(0),
mTimeScale(1.0f),
mUnscaledTime(0),
mTargetFrameTime(0), mSlowMotionTime(0),
mAccTime(0), mSlowTime(0),
mFPS(0)
{
    ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

TimeManager::~TimeManager() = default;

void TimeManager::Init()
{
	QueryPerformanceFrequency(&mFrequency);
	QueryPerformanceCounter(&mLastFrameTime);
	mDeltaTime = 0.0f;
	mTimeScale = 1.0f;
	mUnscaledTime = 0.0f;
	mTargetFrameTime = 1.0f / 60.f;
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&mCurrentFrameTime);
	LONGLONG elapsedTicks = mCurrentFrameTime.QuadPart - mLastFrameTime.QuadPart;
	double elapsedSeconds = static_cast<double>(elapsedTicks) / static_cast<double>(mFrequency.QuadPart);

	mDeltaTime = static_cast<float>(elapsedSeconds) * mTimeScale;
	mUnscaledDeltaTime = static_cast<float>(elapsedSeconds);
	mUnscaledTime += mUnscaledDeltaTime;

	mAccTime += mUnscaledDeltaTime;
	mSlowTime += mUnscaledDeltaTime;

	++mFPS;

	if (mAccTime >= 1.0)
	{
		swprintf_s(m_szFPS, L"FPS : %d", mFPS);
		SetWindowText(g_hWnd, m_szFPS);
		// 1�ʸ��� ����ȭ ����
		mFPS = 0;
		mAccTime = 0;
	}

	if (mSlowTime >= mSlowMotionTime)
	{
		mSlowTime = 0.f;
		mTimeScale = 1.0f;
		mSlowMotionTime = -1.f;
	}

	mLastFrameTime = mCurrentFrameTime;
}

void TimeManager::FrameLimit()
{
	QueryPerformanceCounter(&mCurrentFrameTime);
	LONGLONG elapsedTicks = mCurrentFrameTime.QuadPart - mLastFrameTime.QuadPart;
	double elapsedSeconds = static_cast<double>(elapsedTicks) / static_cast<double>(mFrequency.QuadPart);

	// Wait if frame time is shorter than the target frame time
	while (elapsedSeconds < mTargetFrameTime)
	{
		QueryPerformanceCounter(&mCurrentFrameTime);
		elapsedTicks = mCurrentFrameTime.QuadPart - mLastFrameTime.QuadPart;
		elapsedSeconds = static_cast<double>(elapsedTicks) / static_cast<double>(mFrequency.QuadPart);
	}
}
