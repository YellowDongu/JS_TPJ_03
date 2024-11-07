#pragma once
#include "Scene.h"
#include "Define.h"
#include "ShotPutPlayer.h"
#include "ShotPutBall.h"
#include "ShotPutStadium.h"

class CStage03 : public CScene
{
public:
	CStage03();
	virtual ~CStage03();

public:
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
	void Release() override;

private:
	void Key_Input();

private:
	HDC		m_DC;
	CObj* m_pPlayer;
	CObj* m_pShotPutBall;
	CObj* m_pShotPutStadium;
};
