#include "stdafx.h"
#include "Archer.h"
#include "CScrollMgr.h"

#define scrollMgr CScrollMgr::Get_Instance()


Archer::Archer() : arrow(nullptr)
{
}

Archer::~Archer()
{
}

void Archer::initalize()
{
	position = { 100.0f, 400.0f, 0.0f };

	bow[0] = D3DXVECTOR3{0.0f,70.0f,0.0f };
	bow[1] = D3DXVECTOR3{20.0f,50.0f,0.0f };
	bow[2] = D3DXVECTOR3{20.0f,-50.0f,0.0f };
	bow[3] = D3DXVECTOR3{0.0f,-70.0f,0.0f };

	bowVertex[0] = bow[0];
	bowVertex[1] = bow[1];
	bowVertex[2] = bow[2];
	bowVertex[3] = bow[3];
}

void Archer::render(HDC _hdc)
{
	Rectangle(_hdc, (int)position.x - 50 - scrollMgr->Get_ScrollX(), (int)position.y,
		(int)position.x - scrollMgr->Get_ScrollX(), (int)position.y + 150);

	MoveToEx(_hdc, (int)bowVertex[0].x - scrollMgr->Get_ScrollX(), (int)bowVertex[0].y, nullptr);
	for (int i = 1; i < 4; i++)
	{
		LineTo(_hdc, (int)bowVertex[i].x - scrollMgr->Get_ScrollX(), (int)bowVertex[i].y);
	}
}

void Archer::update()
{
	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(g_hWnd, &mousePos);

	D3DXVECTOR3 diffVector = D3DXVECTOR3{ (float)mousePos.x, (float)mousePos.y, 0.0f} - position;
	D3DXVECTOR3 vector;
	D3DXVec3Normalize(&vector, &diffVector);
	float angle = acosf(vector.x);
	if (diffVector.y < 0)
	{
		angle *= -1;
	}

	D3DXMATRIX rotationMatrix;
	D3DXMATRIX positionMatrix;
	D3DXMatrixTranslation(&positionMatrix, position.x, position.y, position.z);
	D3DXMatrixRotationZ(&rotationMatrix, angle);


	D3DXMATRIX worldMatrix = rotationMatrix * positionMatrix;
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&bowVertex[i], &bow[i], &worldMatrix);
	}
	vector = D3DXVECTOR3{ 1.0f, 0.0f, 0.0f };

	D3DXVec3TransformNormal(&shootDirection, &vector, &worldMatrix);



}

void Archer::release()
{
}

