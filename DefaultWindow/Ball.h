#pragma once
#include "Obj.h"
class Pikachu;

class Ball final : public CObj
{
public:
	Ball(Pikachu* p1, Pikachu* p2);
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

	void Collision();

	void InitFadeBitmap(HDC hDC);

	CollisionDirection DetectBoxCollisionDir(const RECT& objRect, const RECT& otherRect);

private:
	HBITMAP mFadeBitmap;
	D3DXVECTOR2 mAfterEffectPos[2];
	D3DXVECTOR2 mVelocity;
	D3DXVECTOR3 mPrevPosition;
	Pikachu* mPlayer[2];
	float mWidth;
	float mHeight;
	BYTE mOpacity;
	bool mFadeIn;
	bool mFadeOut;
	bool mEffect;
	float mCurrentTime;
	float mEffectTime;
	float mAniTime;
	int mFrame;
};
