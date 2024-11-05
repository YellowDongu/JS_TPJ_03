#pragma once
#include "Scene.h"

class KeyManager;
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

	void UpdateObjects() const;
	void LateUpdateObjects() const;
	void RenderObjects(HDC _hdc) const;
	void CheckCollision();

private:
	std::list<CObj*> 	mObjects;
	KeyManager* 		mKeyManager;
};
