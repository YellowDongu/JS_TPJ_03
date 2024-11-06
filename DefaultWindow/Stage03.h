#pragma once
#include "Scene.h"
#include "Define.h"
#include "ShotPutPlayer.h"
#include "CMonster.h"
#include "ShotPutBall.h"

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
	HDC			m_DC;
	CObj* m_pPlayer;
	CObj* m_pShotPutBall;
};
