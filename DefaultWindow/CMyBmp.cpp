#include "stdafx.h"
#include "CMyBmp.h"

CMyBmp::CMyBmp()
{
}

CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::Load_Bmp(const TCHAR* pFilePath)
{
	HDC			hDC = GetDC(g_hWnd);

	// 매개변수의 dc와 호환되는 dc를 생성해주는 함수
	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,		// 프로그램 인스턴스 핸들을 전달
									pFilePath,	// 파일의 위치 경로
									IMAGE_BITMAP, // 어떤 타입의 파일을 읽어올 지 전달
									0, 0,		 // 이미지의 가로, 세로 사이즈
									LR_LOADFROMFILE | LR_CREATEDIBSECTION); // 파일에서 이미지 불러들임 / 읽어온 파일을 DIB 형태로 변환

	// DDB : 장치에 의존적인 형식 : 이미지의 크기, 색상 등 기본적인 정보와 이미지 데이터로 구성되어 해상도의 장치가 광범위하지 못함
	// DIB : 장치에 독립적인 형식 : 색상 테이블, 해상도 정보 등 추가적인 정보를 가져 장치에 종속되지 않고 활용도 높은 이미지 출력이 가능함

	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

}

void CMyBmp::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);

	DeleteObject(m_hBitmap);

	DeleteDC(m_hMemDC);

}
