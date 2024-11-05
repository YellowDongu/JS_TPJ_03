#include "stdafx.h"
#include "Arrow.h"
#include "TimeManager.h"

<<<<<<< Updated upstream
=======
Arrow::Arrow() : shot(false), angle(0.0f)
{
}

Arrow::~Arrow()
{
}

void Arrow::initalize()
{
	position = D3DXVECTOR3{ 0.0f, 0.0f, 0.0f };
	moveVector = D3DXVECTOR3{ 0.0f, 0.0f, 0.0f };
	initalVertex[0] = D3DXVECTOR3{ 50.0f, 0.0f, 0.0f };
	initalVertex[1] = D3DXVECTOR3{ -50.0f, 0.0f, 0.0f };
	vertex[0] = initalVertex[0];
	vertex[1] = initalVertex[1];
}

void Arrow::render(HDC _hdc)
{
	MoveToEx(_hdc, (int)vertex[0].x, (int)vertex[0].y, nullptr);
	LineTo(_hdc, (int)vertex[1].x, (int)vertex[1].y);

}

void Arrow::update()
{
	if (shot)
	{
		position += moveVector * TimeManager::GetInstance().GetDeltaTime();
		D3DXVECTOR3 vector;
		D3DXVec3Normalize(&vector, &moveVector);

		angle = acosf(vector.x);

		if (moveVector.y < 0)
		{
			angle *= -1;
		}

		 
	}

	D3DXMATRIX rotationMatrix;
	D3DXMATRIX positionMatrix;
	D3DXMatrixTranslation(&positionMatrix, position.x, position.y, position.z );
	D3DXMatrixRotationZ(&rotationMatrix, D3DXToRadian(angle) );

	D3DXMATRIX worldMatrix = rotationMatrix * positionMatrix;

	D3DXVec3TransformCoord(&vertex[0], &initalVertex[0], &worldMatrix);
	D3DXVec3TransformCoord(&vertex[1], &initalVertex[1], &worldMatrix);
}

void Arrow::release()
{
}

void Arrow::shoot(float power)
{
	shot = true;
	moveVector *= power;
}
>>>>>>> Stashed changes
