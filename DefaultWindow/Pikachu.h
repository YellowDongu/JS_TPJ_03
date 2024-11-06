#pragma once
#include "Obj.h"

enum PlayerType
{
	PLAYER01,
	PLAYER02
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

	D3DXVECTOR3* GetVertices() { return mVertices; }
	void AddScore(const int score) { mScore += score; }
	void Move();
	void HandleVelocityInput();
	void UpdateVertex();

private:
	PlayerType mType;
	D3DXVECTOR2 mVelocity;
	D3DXVECTOR3 mVertices[4];
	float mAngle;
	float mWidth;
	float mHeight;
	int mScore;
	bool mSliding;
};

