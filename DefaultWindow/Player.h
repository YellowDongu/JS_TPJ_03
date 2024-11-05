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


// z�� ȸ���� �̿��Ͽ� ��ü�� ȸ����Ű�� ��ũ�� �����϶�
// ���� ����. �� �� ���� ��ȯ�Ͽ� ��Ʈ�� �׸� ��(moveto,lineto�� �׸���� ��)
