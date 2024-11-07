#pragma once
#include "Obj.h"

enum PlayerType
{
	PLAYER01,
	PLAYER02
};

enum State
{
	IDLE,
	JUMP,
	SLIDING,
	SLIDING_FLIP,
	END_STATE
};

class Pikachu final : public CObj
{
public:
	Pikachu(int type);

	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

	D3DXVECTOR3 GetLeftTop();
	D3DXVECTOR3 GetRightBottom();
	bool IsSmash() const { return mSmash; }

	D3DXVECTOR3* GetVertices() { return mVertices; }
	void StartGame();
	void AddScore(const int score) { mScore += score; }
	void Move();
	void HandleVelocityInput();
	void UpdateVertex();
	void UpdateAnimation();

private:
	AniInfo mClip[END_STATE];
	State mState;
	PlayerType mType;
	D3DXVECTOR2 mVelocity;
	D3DXVECTOR2 mOffset;
	D3DXVECTOR3 mVertices[4];
	float mAngle;
	float mWidth;
	float mHeight;
	float mCurrentAniTime;
	int mFrame;
	int mScore;
	bool mSliding;
	bool mSmash;
	bool mJump;
};

