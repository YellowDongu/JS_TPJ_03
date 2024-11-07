#pragma once
#include "Obj.h"
class CShotPutBall : public CObj
{
public:
	CShotPutBall();
	virtual ~CShotPutBall();

public:
	enum LINESTATE { UP, DOWN, END };

public:
	void Initialize() override;
	void Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void LateUpdate() override;

public:
	void		Set_Player(CObj* pPlayer) { m_pPlayer = pPlayer; }
	void		Set_Stop(bool bIsStop) { m_bIsStop = bIsStop; }
	void		Set_CurScore(float fScore) { m_fCurScore = fScore; }
	void		Set_BestScore(float fScore) { m_fBestScore = fScore; }

	void		Get_CurScore(float& fScore) { fScore = m_fCurScore; }
	void		Get_BestScore(float& fScore) { fScore = m_fBestScore; }


private:
	void	SetMatrix();
	void	ScoreCal();
	int		IsPointInLine(D3DXVECTOR3 _vecStartPoint, D3DXVECTOR3 _vecEndPoint);

private:
	bool m_bIsStop;
	float m_fCurScore;
	static float m_fBestScore;
	float m_fSpeedCrashBoundary;
	float m_fXScale;
	float m_fYScale;
	CObj* m_pPlayer;
	D3DXVECTOR3 m_vUpLine[2];
	D3DXVECTOR3 m_vDownLine[2];

};

