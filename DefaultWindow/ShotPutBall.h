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

public:
	void		Set_Player(CObj* pPlayer) { m_pPlayer = pPlayer; }


private:
	CObj* m_pPlayer;
};

