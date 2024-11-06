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

	D3DXVECTOR3 GetLeftTop() const { return mVertices[0]; }
	D3DXVECTOR3 GetRightBottom() const { return mVertices[2]; }

	D3DXVECTOR3* GetVertices() { return mVertices; }
	void Move();
	void HandleVelocityInput();
	void UpdateVertex();

private:
	PlayerType mType;
	D3DXVECTOR2 mVelocity;
	D3DXVECTOR3 mVertices[4];
	float mWidth;
	float mHeight;
	bool mSliding;
};

