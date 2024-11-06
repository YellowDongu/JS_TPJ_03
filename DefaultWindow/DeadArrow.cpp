#include "stdafx.h"
#include "DeadArrow.h"
#include "CScrollMgr.h"

#define scrollMgr CScrollMgr::Get_Instance()



DeadArrow::DeadArrow()
{
}

DeadArrow::~DeadArrow()
{
}

void DeadArrow::init(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	vertex[0] = start;
	vertex[1] = end;
}

void DeadArrow::render(HDC _hdc)
{
	MoveToEx(_hdc, vertex[0].x - scrollMgr->Get_ScrollX(), vertex[0].y, nullptr);
	LineTo(_hdc, vertex[1].x - scrollMgr->Get_ScrollX(), vertex[1].y);
}