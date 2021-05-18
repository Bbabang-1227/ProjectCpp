// ProjectWindows.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#define ON_MAIN
#ifdef ON_MAIN
// ProjectWindows.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "ProjectWindows.h"

#define MAX_LOADSTRING 100
#define MAX_LOADSTRING2 'windowkiki'
#define MAX 5


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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
	_In_ HINSTANCE hInstance, //응용프로그램을 식별하는 값 
	_In_opt_ HINSTANCE hPrevInstance, // 먼저 실행된 인스턴스의 핸들
	_In_ LPWSTR    lpCmdLine, //실행파일의 경로와 명령줄의 내용을 담은 문자열 포인터
	_In_ int       nCmdShow) // 윈도우를 화면에 보여주는 방법을 명시
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PROJECTWINDOWS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{

		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECTWINDOWS));

	/*
	C/C++ 는 함수를 직접 호출하였으며 전체 실행 흐름을 코드에 명시할수있었음
	그러나 윈도우 프로그래밍은 입력을 예측할수없음(비동기)
	언제 발생할지 모르는 비동기 입력에 대해 처리가 가능하면서도 화면이 멈추지말아야한다
	따라서 윈도우 프로그래밍 모델은 Message Driven 방식을 채택
	*/
	MSG msg;

	// 기본 메시지 루프입니다:
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); // 콜백이 있는 함수는 콜백을 먼저 실행해줘야함

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
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
HWND g_mainhWnd;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	g_mainhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr); // 윈도우를 생성

	if (!g_mainhWnd)
	{
		return FALSE;
	}

	ShowWindow(g_mainhWnd, nCmdShow);
	UpdateWindow(g_mainhWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
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
					NULL, //windowname // 보통 클래스네임, 윈도우네임 둘중 한개만 부여함
					WS_CHILD | WS_VISIBLE , //window style
					0 + 100 * i, //x
					0 + 100 * j, //y
					100, //width
					100, //height
					hWnd, //부모핸들
					(HMENU)0, //메뉴
					hInst, //
					NULL
				);

			}
		}
		break;
	}
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
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

		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
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
		// 해당 차일드의 정보를 얻기(x, y)
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
		// 빙고체크
		//1. 가로체크
		
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
				SetProp(g_childhWnd[i][y], _T("modeBINGO"), (HANDLE)(nCurMode+1));//빙고
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		xtrig = 0;
		//2. 세로체크

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
				SetProp(g_childhWnd[x][i], _T("modeBINGO"), (HANDLE)(nCurMode + 1));//빙고
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		xtrig = 0;
		//3. 대각선체크
		//3.1 왼쪽대각선
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
					SetProp(g_childhWnd[i][i], _T("modeBINGO"), (HANDLE)(nCurMode + 1));//빙고
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
					SetProp(g_childhWnd[i][MAX - i - 1], _T("modeBINGO"), (HANDLE)(nCurMode + 1));//빙고
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
		SetProp(hWnd, _T("modeBINGO"), (HANDLE)bingoNONE); //1. 속성 선언
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc2 = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...	


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
// 정보 대화 상자의 메시지 처리기입니다.


#endif  


