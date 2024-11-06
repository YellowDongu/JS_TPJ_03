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



enum CHANNELID
{
	SOUND_EFFECT,
	SOUND_BGM,
	MAXCHANNEL
};

enum CollisionDirection
{
	NONE = 0,
	LEFT = 1 << 0,       // 0001
	RIGHT = 1 << 1,    // 0010
	TOP = 1 << 2,       // 0100
	BOTTOM = 1 << 3    // 1000
};



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





struct tagFinder
{
public:
	tagFinder(const TCHAR* pTag) : m_pTag(pTag) {}

	template<typename T>
	bool	operator()(T& MyPair)
	{
		return !lstrcmp(m_pTag, MyPair.first);
	}

private:
	const TCHAR* m_pTag;
};

struct tagDeleteObj
{
	template<typename T>
	void	operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};


struct tagDeleteMap
{
	template<typename T>
	void	operator()(T& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	}
};



enum SCENEID { SC_LOGO, SC_MENU, SC_EDIT, SC_STAGE, SC_END };

typedef struct tagLinePoint
{

	float	fX;
	float	fY;

	tagLinePoint()
	{
		ZeroMemory(this, sizeof(tagLinePoint));
	}
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOINT;

typedef struct tagLine
{
	LINEPOINT		tLeft;
	LINEPOINT		tRight;

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLeft, LINEPOINT& _tRight)
		: tLeft(_tLeft), tRight(_tRight)
	{
	}

}LINE;