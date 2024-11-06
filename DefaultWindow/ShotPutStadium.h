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
};

