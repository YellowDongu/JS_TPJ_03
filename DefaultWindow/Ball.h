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

private:
	D3DXVECTOR2 mVelocity;
	Pikachu* mPlayer[2];
	float mWidth;
	float mHeight;
};
