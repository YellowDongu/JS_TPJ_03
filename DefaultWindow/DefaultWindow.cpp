// DefaultWindow.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "DefaultWindow.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

HWND	g_hWnd;
HINSTANCE hInst; 
// 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,		// API에서 현재 구동되고 있는 프로그램을 의미
                     _In_opt_ HINSTANCE hPrevInstance, // 전에 실행되었떤 인스턴스의 핸들, 없을 경우 null
                     _In_ LPWSTR    lpCmdLine,	// 
                     _In_ int       nCmdShow)	// 실행한 창의 스타일(모양 / 최소화 OR 최대화 모양) 옵션 변수
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);

	// 창 스타일을 지정하는 옵션 함수
    MyRegisterClass(hInstance);

    // 윈도우 생성 함수
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));

    MSG msg;
	msg.message = WM_NULL;

	CMainGame	MainGame;
	MainGame.Initialize();

	//// 기본 메시지 루프입니다.
	//while (GetMessage(&msg, nullptr, 0, 0))
	//{
	//	// TranslateAccelerator : 메뉴 기능의 단축키가 제대로 작동하도록 검사하는 함수
	//    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	//    {
	//		// 키보드 메세지를 가공하여 프로그램에서 쉽게 사용할 수 있도록 해주는 함수
	//        TranslateMessage(&msg);
	//
	//		// 시스템 메세지 큐에서 꺼낸 메세지를 프로그램의 메세지 처리 함수로 전달하는 함수
	//        DispatchMessage(&msg);
	//    }
	//}

	DWORD dwTime = GetTickCount();
	//dwTime = 1888789593


	while (true)
	{
		// PM_REMOVE : 메세지를 읽어 옴과 동시에 메세지 큐에서 제거
		// PM_NOREMOVE : 메세지 큐에 메세지 존재 여부만 파악, 메세지를 읽어오려면 Getmessage를 다시 호출함

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		else
		{
		
			if (dwTime + 10 < GetTickCount())
			{
				MainGame.Update();
				MainGame.Render();

				dwTime = GetTickCount();
			}
			
		}		
	}


    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;		// 윈도우를 만들기 위해 필요한 구조체

    wcex.cbSize = sizeof(WNDCLASSEX);		// 자기 자신의 사이즈를 저장해 놓음

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
	// 윈도우 스타일을 정의, 어떤 형태를 가질 것인지 지정
	// 초기화 값이 의미하는 것은 윈도우 창의 수직, 수평의 크기가 변할 경우 윈도우를 다시 그린다는 의미
	
    wcex.lpfnWndProc    = WndProc; // 저장해둔 함수가 호출되어 메세지를 처리
	
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
	// 윈도우가 특수한 목적으로 사용하는 여분의 공간
	// 일종의 예약 영역이며 사용하지 않는 경우 0으로 지정

    wcex.hInstance      = hInstance;
	// 윈도우 클래스를 사용하는 프로그램의 번호를 설정

    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);

	// hIcon : 윈도우 사용할 아이콘을 지정(시작 표시줄)
	// hCursor : 윈도우에서 사용할 마우스 커서 지정
	
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	// 윈도우 배경화면

	wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_DEFAULTWINDOW);
	
    wcex.lpszClassName  = szWindowClass;
	// 실행파일 이름

	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	// 윈도우 상단 아이콘

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT	 rc{ 0,0, WINCX, WINCY };

   // rc = rc + 기본 창 스타일 + 메뉴바 사이즈 고려 여부
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   // CreateWindowW : 등록해 놓은 정보들을 토대로 윈도우를 만드는 함수
   HWND hWnd = CreateWindowW(szWindowClass, 
							 szTitle,
							 WS_OVERLAPPEDWINDOW, // 만들고자 하는 윈도우 창의 스타일 지정(기본값)
							 CW_USEDEFAULT, 0,   // 생성되는 창의 x, y 좌표(어디에서부터 창을 그릴 것인가)
							 rc.right - rc.left, 
							 rc.bottom - rc.top,  // 생성되는 창의 가로, 세로 사이즈
							 nullptr,	// 부모 윈도우가 있다면 부모 윈도우 핸들 지정
							 nullptr,	// 윈도우에서 사용할 메뉴의 핸들을 지정
							 hInstance,	 // 윈도우를 만드는 주체, 프로그램 핸들 지정
							 nullptr);	 // 운영체제가 특수한 목적으로 사용

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//


// 1. KERNEL : 메모리를 관리하고 프로그램을 실행
// 2. USER : 유저 인터페이스와 윈도우 생성을 관리
// 3. GDI : 화면 처리와 그래픽을 담당

// DC : 출력에 관한 정보를 갖고 있는 데이터 구조체

// RECT		rc{ 100, 100, 200, 200 };
// list<RECT>	BulletList;
	
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	//case WM_CREATE:
	//	SetTimer(hWnd, 0, 0, 0);
	//
	//	// SetTimer : 타이머를 설치하는 함수
	//	// 1인자 : 윈도우 핸들
	//	// 2인자 : 타이머 id, 여러 개의 타이머가 존재할 수 있기 때문에 0부터 id값 부여
	//	// 3인자 : 타이머 주기, 기본 값으로 지정되어 있는 주기는 1 / 1000초 이다.
	//	// 4인자 : NULL 인 경우 설정한 주기대로 WM_TIMER 메세지를 발생시킴
	//	break;
	//
	//case WM_TIMER:
	//	InvalidateRect(g_hWnd, 0, TRUE);
	//	
	//	// InvalidateRect : 윈도우 화면 갱신 함수
	//	// 1인자 : 갱신할 윈도우의 핸들을 넣어줌
	//	// 2인자 : 윈도우 안에서 갱신할 범위를 지정,NULL인 경우 전체 영역
	//	// 3인자 : TRUE인 경우 그려져 있지 않은 부분도 갱신
	//	//        FALSE : 새로 그리는 부분만 갱신
	//
	//	break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

		/*case VK_RIGHT:
			rc.left  += 10;
			rc.right += 10;
			break;

		case VK_LEFT:
			rc.left -= 10;
			rc.right -= 10;
			break;

		case VK_UP:
			rc.top    -= 10;
			rc.bottom -= 10;
			break;

		case VK_DOWN:
			rc.top	  += 10;
			rc.bottom += 10;
			break;

		case VK_SPACE:

			BulletList.push_back(rc);

			break;*/
		}
		break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(g_hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

   // case WM_PAINT:
   //     {
   //         PAINTSTRUCT ps;

   //         HDC hdc = BeginPaint(hWnd, &ps);	// hWnd 에 해당하는 창의 DC를 얻어 올 수 있음
			//// GetDC(HWND)

			//// 그리기 함수
			//
			//// MoveToEx : 커서의 위치를 이동시키는 함수(nullptr : 커서를 이동하기 전 위치를 output의 형태로 반환)
			////MoveToEx(hdc, 100, 100, nullptr);

			////LineTo : 매개 변수로 전달한 값까지 선을 그리는 함수
			////LineTo(hdc, 200, 200);

			////LineTo(hdc, 200, 300);
			//
			//// MoveToEx(hdc, 100, 100, nullptr);
			//// LineTo(hdc, 200, 100);
			//// LineTo(hdc, 200, 200);
			//// LineTo(hdc, 100, 200);
			//// LineTo(hdc, 100, 100);
			//// 
			//// LineTo(hdc, 200, 200);
			//// 
			//// MoveToEx(hdc, 200, 100, nullptr);
			//// LineTo(hdc, 100, 200);

			//// Rectangle : 사각형 그리기 함수
			////Rectangle(hdc, 100, 100, 200, 200);

			//// Ellipse : 원 그리기 함수
			////Ellipse(hdc, 300, 300, 400, 400);

			//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

			//for (auto& iter : BulletList)
			//{
			//	Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);

			//	iter.top -= 10;
			//	iter.bottom -= 10;
			//}

			//EndPaint(hWnd, &ps);
   //     }
   //     break;


    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// 함수 호출 규약

// 함수의 실행이 종료되면 할당되었던 STACK 메모리를 해제해야 한다. 
// 이 때 함수를 호출한 호출원(caller)에서 정리할 것인지 아니면 호출 받은 피호출자(callee)에서 할 것인지에 대한 규칙이 존재한다.
// 이런 규칙을 '함수 호출 규약'이라 한다

// __cdecl : c/ c++언어의 기본 호출 규약, caller가 stack 메모리를 정리, 자기 자신에게 어떤 매개 변수가 얼마나 들어올지 모르는 형태의 함수(가변 인자 함수)
// --------------------------------------------------------------------------------------
// __stdcall :  win32 api 기본 호출 규약, callee stack 메모리를 정리, api 에서 제공하는 대부분의 함수들은 '고정 인자 함수'
// __thiscall : this 포인터를 매개변수로 넘겨 받았을 때 사용하는 호출 규약,  callee stack 메모리를 정리
// __fastcall : 함수 호출을 빠르게 처리하기위한 규약, ecx와 edx라는 레지스터를 통해 저장,  callee stack 메모리를 정리
 

// 1. 그림을 그려와라

