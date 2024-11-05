#pragma once
#include "Arrow.h"


class Archer
{
public:
	Archer();
	~Archer();

	void initalize();
	void render(HDC _hdc);
	void update();
	void release();



private:

	Arrow* arrow;

	D3DXVECTOR3 shootDirection;
	D3DXVECTOR3 bowString;

	D3DXVECTOR3 bow[4];


};

Archer::Archer()
{
}

Archer::~Archer()
{
}