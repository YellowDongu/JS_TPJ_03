#pragma once
#include "Obj.h"
class CShotPutStadium : public CObj
{
public:
	CShotPutStadium();
	virtual ~CShotPutStadium();

public:
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	const TCHAR* m_pFrameKey;
	D3DXVECTOR3 m_vUpLine[2];
	D3DXVECTOR3 m_vDownLine[2];
	D3DXVECTOR3 m_vStartStand[2];
};

