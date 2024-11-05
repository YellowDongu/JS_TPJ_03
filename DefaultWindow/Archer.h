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

	const D3DXVECTOR3& getPosition() const { return position; }
	const D3DXVECTOR3& getDirection() const { return shootDirection; }

private:
	Arrow* arrow;

	D3DXVECTOR3 position;
	D3DXVECTOR3 shootDirection;
	//D3DXVECTOR3 bowString;

	D3DXVECTOR3 bow[4];
	D3DXVECTOR3 bowVertex[4];

};