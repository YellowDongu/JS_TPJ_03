#pragma once
#include "Scene.h"

class CStage03 : public CScene
{
public:
	CStage03();
	virtual ~CStage03();

	// CScene을(를) 통해 상속됨
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
	void Release() override;
private:
};
