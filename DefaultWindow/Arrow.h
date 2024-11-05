#pragma once


class Arrow
{
public:
	Arrow();
	~Arrow();

	void initalize();
	void render(HDC _hdc);
	void update();
	void release();

	void shoot(D3DXVECTOR3 towards);
private:
	D3DXVECTOR3 positionVector;
	D3DXVECTOR3 moveVector;
	D3DXVECTOR3 vertex[2];
	D3DXVECTOR3 initalVertex[2];

};
