#pragma once
#include "Obj.h"
class Pikachu final : public CObj
{
public:
	Pikachu() = default;

	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

	void Move();
	void HandleVelocityInput();
	void UpdateVertex();

private:
	D3DXVECTOR2 mVelocity;
	D3DXVECTOR3 mVertices[4];
	float mWidth;
	float mHeight;
};

