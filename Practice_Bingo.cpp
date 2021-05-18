// ProjectWindows.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//
#define ON_MAIN
#ifdef ON_MAIN
// ProjectWindows.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "ProjectWindows.h"

#define MAX_LOADSTRING 100
#define MAX_LOADSTRING2 'windowkiki'
#define MAX 5


// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK    ChildProc(HWND, UINT, WPARAM, LPARAM); //child
HWND hC1;


BOOL g_bMyTurn = TRUE;
enum modeBINGO {
	bingoNONE = 0,
	bingoMINE,
	bingoMyBINGO,
	bingoYOURS,
	bingoYourBingo
};


int APIENTRY wWinMain(// main
	_In_ HINSTANCE hInstance, //�������α׷��� �ĺ��ϴ� �� 
	_In_opt_ HINSTANCE hPrevInstance, // ���� ����� �ν��Ͻ��� �ڵ�
	_In_ LPWSTR    lpCmdLine, //���������� ��ο� ������� ������ ���� ���ڿ� ������
	_In_ int       nCmdShow) // �����츦 ȭ�鿡 �����ִ� ����� ���
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PROJECTWINDOWS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���ø����̼� �ʱ�ȭ�� �����մϴ�:
	if (!InitInstance(hInstance, nCmdShow))
	{

		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECTWINDOWS));

	/*
	C/C++ �� �Լ��� ���� ȣ���Ͽ����� ��ü ���� �帧�� �ڵ忡 ����Ҽ��־���
	�׷��� ������ ���α׷����� �Է��� �����Ҽ�����(�񵿱�)
	���� �߻����� �𸣴� �񵿱� �Է¿� ���� ó���� �����ϸ鼭�� ȭ���� ���������ƾ��Ѵ�
	���� ������ ���α׷��� ���� Message Driven ����� ä��
	*/
	MSG msg;

	// �⺻ �޽��� �����Դϴ�:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); // �ݹ��� �ִ� �Լ��� �ݹ��� ���� �����������

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECTWINDOWS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PROJECTWINDOWS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wcex);
	//child
	wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
	wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wcex.lpfnWndProc = ChildProc;
	wcex.lpszClassName = _T("lpszClass");
	RegisterClassExW(&wcex);

	return 0;
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ�:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
HWND g_mainhWnd;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	g_mainhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr); // �����츦 ����

	if (!g_mainhWnd)
	{
		return FALSE;
	}

	ShowWindow(g_mainhWnd, nCmdShow);
	UpdateWindow(g_mainhWnd);

	return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//

HWND g_childhWnd[5][5];
#define WM_CHECKBINGO WM_USER + 1

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_CREATE:
	{
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				g_childhWnd[i][j] = CreateWindow(
					_T("lpszClass"), //classname
					NULL, //windowname // ���� Ŭ��������, ��������� ���� �Ѱ��� �ο���
					WS_CHILD | WS_VISIBLE , //window style
					0 + 100 * i, //x
					0 + 100 * j, //y
					100, //width
					100, //height
					hWnd, //�θ��ڵ�
					(HMENU)0, //�޴�
					hInst, //
					NULL
				);

			}
		}
		break;
	}
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		// �޴� ������ ���� �м��մϴ�:
		switch (wmId)
		{
		case IDM_ABOUT:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
					 break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_CHECKBINGO:
	{
		g_bMyTurn = !g_bMyTurn; 
		if(g_bMyTurn)
			SetWindowText(hWnd, _T("My Turn"));
		else
			SetWindowText(hWnd, _T("Your Turn"));
		
		///////////////////////////////////////////////
		// �ش� ���ϵ��� ������ ���(x, y)
		HWND hChild = (HWND)wParam;
		int nCurMode = (int)lParam;

		int x = -1;
		int y = -1;
		int xtrig = 0;
		//int ytrig = 0;
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				if (g_childhWnd[i][j] == hChild)
				{
					x = i;
					y = j;
					break;
				}
			}
		}
		if (x < 0 || y < 0) return 0;

		///////////////////////////////////////////////
		// ����üũ
		//1. ����üũ
		
		for (int i = 0; i < MAX; i++)
		{
			int temp = (int)GetProp(g_childhWnd[i][y], _T("modeBINGO"));
			if (temp == nCurMode || temp == nCurMode+1)
			{
				xtrig++;
			}
		}
		if (xtrig == MAX)
		{
			for (int i = 0; i < MAX; i++)
			{
				SetProp(g_childhWnd[i][y], _T("modeBINGO"), (HANDLE)(nCurMode+1));//����
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		xtrig = 0;
		//2. ����üũ

		for (int i = 0; i < MAX; i++)
		{
			int temp = (int)GetProp(g_childhWnd[x][i], _T("modeBINGO"));
			if (temp == nCurMode || temp == nCurMode + 1)
			{
				xtrig++;
			}
		}
		if (xtrig == MAX)
		{
			for (int i = 0; i < MAX; i++)
			{
				SetProp(g_childhWnd[x][i], _T("modeBINGO"), (HANDLE)(nCurMode + 1));//����
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		xtrig = 0;
		//3. �밢��üũ
		//3.1 ���ʴ밢��
		if (x == y)
		{
			for (int i = 0; i < MAX; i++)
			{
				int temp = (int)GetProp(g_childhWnd[i][i], _T("modeBINGO"));
				if (temp == nCurMode || temp == nCurMode + 1)
				{
					xtrig++;
				}
			}
			if (xtrig == MAX)
			{
				for (int i = 0; i < MAX; i++)
				{
					SetProp(g_childhWnd[i][i], _T("modeBINGO"), (HANDLE)(nCurMode + 1));//����
					InvalidateRect(hWnd, NULL, TRUE);
				}
			}
		}
		xtrig = 0;
		if (x + y == MAX - 1)
		{
			for (int i = 0; i < MAX; i++)
			{
				int temp = (int)GetProp(g_childhWnd[i][MAX - i - 1], _T("modeBINGO"));
				if (temp == nCurMode || temp == nCurMode + 1)
				{
					xtrig++;
				}
			}
			if (xtrig == MAX)
			{
				for (int i = 0; i < MAX; i++)
				{
					SetProp(g_childhWnd[i][MAX - i - 1], _T("modeBINGO"), (HANDLE)(nCurMode + 1));//����
					InvalidateRect(hWnd, NULL, TRUE);
				}
			}
		}
		xtrig = 0;
		break;
	}

	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

BOOL bEllipse = TRUE;

LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int mState;

	switch (message)
	{
	case WM_CREATE:
	{
		SetProp(hWnd, _T("modeBINGO"), (HANDLE)bingoNONE); //1. �Ӽ� ����
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc2 = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...	


		mState = (int)GetProp(hWnd, _T("modeBINGO"));
		if (mState == bingoNONE)
		{
			Rectangle(hdc2, 10, 10, 80, 80);
		}
		else if (mState == bingoMINE)
		{
			Ellipse(hdc2, 10, 10, 80, 80);

		}
		else if (mState == bingoYOURS)
		{
			MoveToEx(hdc2, 10, 10, NULL);
			LineTo(hdc2, 90, 90);
			MoveToEx(hdc2, 90, 10, NULL);
			LineTo(hdc2, 10, 90);

		}
		else if (mState == bingoMyBINGO)
		{
			HBRUSH MyBr2 = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
			SelectObject(hdc2, MyBr2);
			Ellipse(hdc2, 10, 10, 80, 80);
			
		}
		else
		{
			HBRUSH MyBr2 = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc2, MyBr2);
			Rectangle(hdc2, 10, 10, 80, 80);
		}
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_LBUTTONDOWN:
	{

		mState = (int)GetProp(hWnd, _T("modeBINGO"));
		if (mState == bingoNONE)
		{
			int nMode;
			if (g_bMyTurn)
			{
				nMode = bingoMINE;
			}
			else
			{
				nMode = bingoYOURS;				
			}
			SetProp(hWnd, _T("modeBINGO"), (HANDLE)nMode);
			SendMessage(g_mainhWnd, WM_CHECKBINGO, (WPARAM)hWnd, nMode); 		
			
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_DESTROY:
	{
		RemoveProp(hWnd, _T("bEllipse"));
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
// ���� ��ȭ ������ �޽��� ó�����Դϴ�.


#endif  


