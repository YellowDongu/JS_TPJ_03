#include "stdafx.h"
#include "Arrow.h"


Arrow::Arrow()
{
}

Arrow::~Arrow()
{
}

void Arrow::initalize()
{
	positionVector = D3DXVECTOR3{ 0.0f, 0.0f, 0.0f };
	moveVector = D3DXVECTOR3{ 0.0f, 0.0f, 0.0f };
	initalVertex[0] = D3DXVECTOR3{ 10.0f, 0.0f, 0.0f };
	initalVertex[1] = D3DXVECTOR3{ -10.0f, 0.0f, 0.0f };
	vertex[0] = initalVertex[0];
	vertex[1] = initalVertex[1];
}

void Arrow::render(HDC _hdc)
{
}

void Arrow::update()
{
}

void Arrow::release()
{
}

void Arrow::shoot(D3DXVECTOR3 towards)
{

}
