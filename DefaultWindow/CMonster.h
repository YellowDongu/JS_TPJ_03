#pragma once
#include "Obj.h"
class CMonster :    public CObj
{
public:
	CMonster();
	~CMonster();

public:
	void		Set_Player(CObj* pPlayer) { m_pPlayer = pPlayer; }

public:
	void Initialize() override;
	void Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	CObj* m_pPlayer;
};

