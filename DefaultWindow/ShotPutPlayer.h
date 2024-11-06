#pragma once
#include "Obj.h"
class CShotPutPlayer : public CObj
{
public:
	CShotPutPlayer();
	virtual ~CShotPutPlayer();

public:
	void Initialize() override;
	void Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void LateUpdate() override;
public:
	void	SetAngle(float fAngle) { m_fAngle = fAngle; }
	void	SetRotSpeed(float fRotSpeed) { m_fRotSpeed = fRotSpeed; }
	void	SetPosinAngle(float fPosinAngle) { m_fPosinAngle = fPosinAngle; }
	void	SetXSacle(float fXSacle) { m_fXSacle = fXSacle; }
	void	SetYSacle(float fYSacle) { m_fYSacle = fYSacle; }

	bool	GetIsRot() { return m_bIsRot; }
	float	GetAngle() { return m_fAngle; }
	float	GetRotSpeed() { return m_fRotSpeed; }
	float	GetPosinAngle() { return m_fPosinAngle; }
	float	GetXSacle() { return m_fXSacle; }
	float	GetYSacle() { return m_fYSacle; }


private:
	void KeyInput();
	void SetMatrix();

private:
	bool m_bIsRot;
	float m_fAngle;
	float m_fRotSpeed;
	float m_fPosinAngle;
	float m_fXSacle;
	float m_fYSacle;
	D3DXMATRIX matScale;
	D3DXMATRIX matRotZ;
	D3DXMATRIX matTrans;


};

