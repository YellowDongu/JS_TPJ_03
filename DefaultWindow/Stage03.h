#pragma once
#include "Scene.h"

class CStage03 : public CScene
{
public:
	CStage03();
	virtual ~CStage03();

	// CScene��(��) ���� ��ӵ�
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
	void Release() override;
private:
};
