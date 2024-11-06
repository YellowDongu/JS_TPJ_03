#pragma once
#include "Obj.h"
class CShotPutBall : public CObj
{
public:
	CShotPutBall();
	virtual ~CShotPutBall();

public:
	void Initialize() override;
	void Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void LateUpdate() override;

public:
	void		Set_Player(CObj* pPlayer) { m_pPlayer = pPlayer; }

private:
	void		SetMatrix();
	void		ScoreCal();

private:
	float m_fScore;
	float m_fSpeedCrashBoundary;
	float m_fXScale;
	float m_fYScale;
	CObj* m_pPlayer;

};

