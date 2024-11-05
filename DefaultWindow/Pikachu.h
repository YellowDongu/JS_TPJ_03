#pragma once
#include "Obj.h"
class Pikachu : public CObj
{
public:
	void Initialize() override;
	void Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

