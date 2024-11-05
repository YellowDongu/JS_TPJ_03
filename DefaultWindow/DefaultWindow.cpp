// DefaultWindow.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "DefaultWindow.h"
#include "MainGame.h"
#include "TimeManager.h"

#define MAX_LOADSTRING 100

HWND	g_hWnd;
HINSTANCE hInst; 
// ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,		// API���� ���� �����ǰ� �ִ� ���α׷��� �ǹ�
                     _In_opt_ HINSTANCE hPrevInstance, // ���� ����Ǿ��� �ν��Ͻ��� �ڵ�, ���� ��� null
                     _In_ LPWSTR    lpCmdLine,	// 
                     _In_ int       nCmdShow)	// ������ â�� ��Ÿ��(��� / �ּ�ȭ OR �ִ�ȭ ���) �ɼ� ����
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);

	// â ��Ÿ���� �����ϴ� �ɼ� �Լ�
    MyRegisterClass(hInstance);

    // ������ ���� �Լ�
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));

    MSG msg;
	msg.message = WM_NULL;

	CMainGame	MainGame;
	MainGame.Initialize();

	TimeManager* TimeManager = &TimeManager::GetInstance();
	TimeManager->Init();

	//// �⺻ �޽��� �����Դϴ�.
	//while (GetMessage(&msg, nullptr, 0, 0))
	//{
	//	// TranslateAccelerator : �޴� ����� ����Ű�� ����� �۵��ϵ��� �˻��ϴ� �Լ�
	//    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	//    {
	//		// Ű���� �޼����� �����Ͽ� ���α׷����� ���� ����� �� �ֵ��� ���ִ� �Լ�
	//        TranslateMessage(&msg);
	//
	//		// �ý��� �޼��� ť���� ���� �޼����� ���α׷��� �޼��� ó�� �Լ��� �����ϴ� �Լ�
	//        DispatchMessage(&msg);
	//    }
	//}

	DWORD dwTime = GetTickCount();
	//dwTime = 1888789593


	while (true)
	{
		// PM_REMOVE : �޼����� �о� �Ȱ� ���ÿ� �޼��� ť���� ����
		// PM_NOREMOVE : �޼��� ť�� �޼��� ���� ���θ� �ľ�, �޼����� �о������ Getmessage�� �ٽ� ȣ����

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
			// Ÿ�� �Ŵ����� Update�� FrameLimit�� �ݵ�� �� �հ� �� �ڿ� �־���մϴ�.
			TimeManager::GetInstance().Update();
			MainGame.Update();
			MainGame.Render();
			TimeManager::GetInstance().FrameLimit();
		}		
	}


    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;		// �����츦 ����� ���� �ʿ��� ����ü

    wcex.cbSize = sizeof(WNDCLASSEX);		// �ڱ� �ڽ��� ����� ������ ����

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
	// ������ ��Ÿ���� ����, � ���¸� ���� ������ ����
	// �ʱ�ȭ ���� �ǹ��ϴ� ���� ������ â�� ����, ������ ũ�Ⱑ ���� ��� �����츦 �ٽ� �׸��ٴ� �ǹ�
	
    wcex.lpfnWndProc    = WndProc; // �����ص� �Լ��� ȣ��Ǿ� �޼����� ó��
	
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
	// �����찡 Ư���� �������� ����ϴ� ������ ����
	// ������ ���� �����̸� ������� �ʴ� ��� 0���� ����

    wcex.hInstance      = hInstance;
	// ������ Ŭ������ ����ϴ� ���α׷��� ��ȣ�� ����

    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);

	// hIcon : ������ ����� �������� ����(���� ǥ����)
	// hCursor : �����쿡�� ����� ���콺 Ŀ�� ����
	
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	// ������ ���ȭ��

	wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_DEFAULTWINDOW);
	
    wcex.lpszClassName  = szWindowClass;
	// �������� �̸�

	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	// ������ ��� ������

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   RECT	 rc{ 0,0, WINCX, WINCY };

   // rc = rc + �⺻ â ��Ÿ�� + �޴��� ������ ��� ����
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   // CreateWindowW : ����� ���� �������� ���� �����츦 ����� �Լ�
   HWND hWnd = CreateWindowW(szWindowClass, 
							 szTitle,
							 WS_OVERLAPPEDWINDOW, // ������� �ϴ� ������ â�� ��Ÿ�� ����(�⺻��)
							 CW_USEDEFAULT, 0,   // �����Ǵ� â�� x, y ��ǥ(��𿡼����� â�� �׸� ���ΰ�)
							 rc.right - rc.left, 
							 rc.bottom - rc.top,  // �����Ǵ� â�� ����, ���� ������
							 nullptr,	// �θ� �����찡 �ִٸ� �θ� ������ �ڵ� ����
							 nullptr,	// �����쿡�� ����� �޴��� �ڵ��� ����
							 hInstance,	 // �����츦 ����� ��ü, ���α׷� �ڵ� ����
							 nullptr);	 // �ü���� Ư���� �������� ���

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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//


// 1. KERNEL : �޸𸮸� �����ϰ� ���α׷��� ����
// 2. USER : ���� �������̽��� ������ ������ ����
// 3. GDI : ȭ�� ó���� �׷����� ���

// DC : ��¿� ���� ������ ���� �ִ� ������ ����ü

// RECT		rc{ 100, 100, 200, 200 };
// list<RECT>	BulletList;
	
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	//case WM_CREATE:
	//	SetTimer(hWnd, 0, 0, 0);
	//
	//	// SetTimer : Ÿ�̸Ӹ� ��ġ�ϴ� �Լ�
	//	// 1���� : ������ �ڵ�
	//	// 2���� : Ÿ�̸� id, ���� ���� Ÿ�̸Ӱ� ������ �� �ֱ� ������ 0���� id�� �ο�
	//	// 3���� : Ÿ�̸� �ֱ�, �⺻ ������ �����Ǿ� �ִ� �ֱ�� 1 / 1000�� �̴�.
	//	// 4���� : NULL �� ��� ������ �ֱ��� WM_TIMER �޼����� �߻���Ŵ
	//	break;
	//
	//case WM_TIMER:
	//	InvalidateRect(g_hWnd, 0, TRUE);
	//	
	//	// InvalidateRect : ������ ȭ�� ���� �Լ�
	//	// 1���� : ������ �������� �ڵ��� �־���
	//	// 2���� : ������ �ȿ��� ������ ������ ����,NULL�� ��� ��ü ����
	//	// 3���� : TRUE�� ��� �׷��� ���� ���� �κе� ����
	//	//        FALSE : ���� �׸��� �κи� ����
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
            // �޴� ������ ���� �м��մϴ�.
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

   //         HDC hdc = BeginPaint(hWnd, &ps);	// hWnd �� �ش��ϴ� â�� DC�� ��� �� �� ����
			//// GetDC(HWND)

			//// �׸��� �Լ�
			//
			//// MoveToEx : Ŀ���� ��ġ�� �̵���Ű�� �Լ�(nullptr : Ŀ���� �̵��ϱ� �� ��ġ�� output�� ���·� ��ȯ)
			////MoveToEx(hdc, 100, 100, nullptr);

			////LineTo : �Ű� ������ ������ ������ ���� �׸��� �Լ�
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

			//// Rectangle : �簢�� �׸��� �Լ�
			////Rectangle(hdc, 100, 100, 200, 200);

			//// Ellipse : �� �׸��� �Լ�
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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

// �Լ� ȣ�� �Ծ�

// �Լ��� ������ ����Ǹ� �Ҵ�Ǿ��� STACK �޸𸮸� �����ؾ� �Ѵ�. 
// �� �� �Լ��� ȣ���� ȣ���(caller)���� ������ ������ �ƴϸ� ȣ�� ���� ��ȣ����(callee)���� �� �������� ���� ��Ģ�� �����Ѵ�.
// �̷� ��Ģ�� '�Լ� ȣ�� �Ծ�'�̶� �Ѵ�

// __cdecl : c/ c++����� �⺻ ȣ�� �Ծ�, caller�� stack �޸𸮸� ����, �ڱ� �ڽſ��� � �Ű� ������ �󸶳� ������ �𸣴� ������ �Լ�(���� ���� �Լ�)
// --------------------------------------------------------------------------------------
// __stdcall :  win32 api �⺻ ȣ�� �Ծ�, callee stack �޸𸮸� ����, api ���� �����ϴ� ��κ��� �Լ����� '���� ���� �Լ�'
// __thiscall : this �����͸� �Ű������� �Ѱ� �޾��� �� ����ϴ� ȣ�� �Ծ�,  callee stack �޸𸮸� ����
// __fastcall : �Լ� ȣ���� ������ ó���ϱ����� �Ծ�, ecx�� edx��� �������͸� ���� ����,  callee stack �޸𸮸� ����
 

// 1. �׸��� �׷��Ͷ�

