#include "stdafx.h"
#include "ShotPutStadium.h"
#include "CBmpMgr.h"

CShotPutStadium::CShotPutStadium()
{
	ZeroMemory(&m_vUpLine, sizeof(D3DXVECTOR3) * 2);
	ZeroMemory(&m_vDownLine, sizeof(D3DXVECTOR3) * 2);
	ZeroMemory(&m_vStartStand, sizeof(D3DXVECTOR3) * 2);
}

CShotPutStadium::~CShotPutStadium()
{
	Release();
}

void CShotPutStadium::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ShotPutMap.bmp", L"ShotPutMap");

	m_pFrameKey = L"ShotPutMap";

	// 위치 조정 하고 색 채우기 ㅋㅋ
	m_vUpLine[0] = { 220.f, 250.f, 0.f }; // LeftTop
	m_vUpLine[1] = { 800.f, 0.f, 0.f }; // RightBottom

	m_vDownLine[0] = { 220.f, 350.f, 0.f }; // LeftTop
	m_vDownLine[1] = { 800.f, 600.f, 0.f }; // RightBottom

	m_vStartStand[0] = { 100.f, 225.f, 0.f }; // LeftTop
	m_vStartStand[1] = { 255.f, 375.f, 0.f }; // RightBottom
}

void CShotPutStadium::Update()
{
}

void CShotPutStadium::LateUpdate()
{

}

void CShotPutStadium::Render(HDC hDC)
{
	HDC hMemDc = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDc, 0, 0, SRCCOPY);


	//MoveToEx(hDC, m_vUpLine[0].x, m_vUpLine[0].y, nullptr);
	//LineTo(hDC, m_vUpLine[1].x, m_vUpLine[1].y);
	//
	//MoveToEx(hDC, m_vDownLine[0].x, m_vDownLine[0].y, nullptr);
	//LineTo(hDC, m_vDownLine[1].x, m_vDownLine[1].y);

	//Ellipse(hDC, m_vStartStand[0].x, m_vStartStand[0].y, m_vStartStand[1].x, m_vStartStand[1].y);
}

void CShotPutStadium::Release()
{
}
