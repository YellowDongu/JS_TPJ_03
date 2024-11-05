#pragma once

#define			WINCX		800
#define			WINCY		600

#define			PURE		= 0 

#define 		VK_MAX		0xff

extern			HWND		g_hWnd;

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;			// 위치 벡터
	D3DXVECTOR3		vDir;			// 방향 벡터
	D3DXVECTOR3		vLook;

	D3DXVECTOR3		vNormal;		// 법선 벡터(방향 벡터)

	D3DXMATRIX		matWorld;
	
}INFO;


template<typename T>
void Safe_Delete(T& Tmp)
{
	if (Tmp)
	{
		delete Tmp;
		Tmp = nullptr;
	}
}

static D3DXVECTOR3		Get_Mouse()
{
	POINT	ptMouse{};

	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	return D3DXVECTOR3((float)ptMouse.x, (float)ptMouse.y, 0.f);
}
