#pragma once


class DeadArrow
{
public:
	DeadArrow();
	~DeadArrow();

	void init(D3DXVECTOR3 start, D3DXVECTOR3 end);
	void render(HDC _hdc);

private:
	D3DXVECTOR3 vertex[2];
};
