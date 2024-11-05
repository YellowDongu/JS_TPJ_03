#pragma once
#include "Scene.h"

class CStage01 : public CScene
{
public:
	CStage01();
	virtual ~CStage01();

	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
	void Release() override;
private:
	int mTest;
};
