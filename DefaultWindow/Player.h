#pragma once
#include "Obj.h"
class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	void		LateUpdate();
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void	Key_Input();
};


// z축 회전을 이용하여 몸체를 회전시키는 탱크를 구현하라
// 주의 사항. 점 네 개를 변환하여 렉트를 그릴 것(moveto,lineto로 그리라는 뜻)
