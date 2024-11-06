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

	// �Ű������� dc�� ȣȯ�Ǵ� dc�� �������ִ� �Լ�
	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,		// ���α׷� �ν��Ͻ� �ڵ��� ����
									pFilePath,	// ������ ��ġ ���
									IMAGE_BITMAP, // � Ÿ���� ������ �о�� �� ����
									0, 0,		 // �̹����� ����, ���� ������
									LR_LOADFROMFILE | LR_CREATEDIBSECTION); // ���Ͽ��� �̹��� �ҷ����� / �о�� ������ DIB ���·� ��ȯ

	// DDB : ��ġ�� �������� ���� : �̹����� ũ��, ���� �� �⺻���� ������ �̹��� �����ͷ� �����Ǿ� �ػ��� ��ġ�� ���������� ����
	// DIB : ��ġ�� �������� ���� : ���� ���̺�, �ػ� ���� �� �߰����� ������ ���� ��ġ�� ���ӵ��� �ʰ� Ȱ�뵵 ���� �̹��� ����� ������

	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

}

void CMyBmp::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);

	DeleteObject(m_hBitmap);

	DeleteDC(m_hMemDC);

}
