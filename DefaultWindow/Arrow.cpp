#include "stdafx.h"
#include "Arrow.h"
#include "TimeManager.h"
#include "CScrollMgr.h"

#define scrollMgr CScrollMgr::Get_Instance()

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
	MoveToEx(_hdc, (int)vertex[0].x - scrollMgr->Get_ScrollX(), (int)vertex[0].y, nullptr);
	LineTo(_hdc, (int)vertex[1].x - scrollMgr->Get_ScrollX(), (int)vertex[1].y);
}

void Arrow::update()
{
	D3DXVECTOR3 vector = {-1.0f, 100.0f, 0.0f};
	if (shot)
	{
		position += moveVector * TimeManager::GetInstance().GetDeltaTime();

		moveVector += vector * TimeManager::GetInstance().GetDeltaTime();
	}

	D3DXVec3Normalize(&vector, &moveVector);

	angle = acosf(vector.x);
	if (moveVector.y < 0)
	{
		angle *= -1;
	}

	D3DXMATRIX rotationMatrix;
	D3DXMATRIX positionMatrix;
	D3DXMatrixTranslation(&positionMatrix, position.x, position.y, position.z );
	D3DXMatrixRotationZ(&rotationMatrix, angle);

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

bool Arrow::collision()
{
	if (vertex[0].y > 550.0f || vertex[1].y > 550.0f)
		return true;

	if (vertex[0].x > 5000.0f || vertex[1].x > 5000.0f)
		return true;

	if (vertex[0].x > 997.0f && vertex[0].x < 1005.0f &&
		vertex[0].y > 300.0f && vertex[0].y < 530.0f)
	{
		return true;
	}
	return false;
}
