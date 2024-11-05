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


private:
	D3DXVECTOR3 positionVector;
	D3DXVECTOR3 moveVector;
	D3DXVECTOR3 vertex[2];

};

Arrow::Arrow()
{
}

Arrow::~Arrow()
{
}