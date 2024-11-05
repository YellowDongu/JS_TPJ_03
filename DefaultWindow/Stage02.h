#pragma once
#include "Scene.h"
#include "Archer.h"

class CStage02 : public CScene
{
public:
	CStage02();
	virtual ~CStage02();

	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
	void Release() override;

private:
	float power;


	Archer* archer;
	Arrow* arrow;


};