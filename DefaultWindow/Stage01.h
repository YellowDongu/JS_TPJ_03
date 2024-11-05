#pragma once
#include "KeyManager.h"
#include "Scene.h"

class CObj;

class CStage01 : public CScene
{
public:
	CStage01();
	~CStage01() override;

	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
	void Release() override;

private:
	KeyManager* 		mKeyManager;
	std::list<CObj*> 	mObjects;
};
