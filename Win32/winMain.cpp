#include "stdafx.h"
#include "Framework.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

namespace {
	TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
	TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.

	CFramework g_Framework;
	
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
		//	메인 윈도우 핸들
		HWND hWnd;

		//	윈도우 스타일
		DWORD dwStyle = 
				  WS_OVERLAPPED 	//	
				| WS_CAPTION 		//
				| WS_MINIMIZEBOX 	//
				| WS_SYSMENU 		//
				| WS_BORDER			//
				;					//	end

		//	인스턴스 핸들을 전역 변수에 저장
		hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

		//	데스크톱 윈도우 사이즈
		RECT getWinSize;
		GetWindowRect(GetDesktopWindow(), &getWinSize);

		//	클라이언트 사이즈
		RECT rc;
		rc.left = rc.top = 0;
		rc.right = CLIENT_WIDTH;
		rc.bottom = CLIENT_HEIGHT;
		AdjustWindowRect(&rc, dwStyle, FALSE);
	
		//	클라이언트 절대좌표(left, top)
		POINT ptClientWorld;
		ptClientWorld.x = (getWinSize.right - CLIENT_WIDTH) / 2;
		ptClientWorld.y = (getWinSize.bottom - CLIENT_HEIGHT) / 2;

		//	윈도우 생성
		hWnd = CreateWindow(
					  szWindowClass			//	윈도우 클래스 명
					, szTitle				//	캡션 표시 문자열
					, dwStyle				//	윈도우 스타일
					, ptClientWorld.x		//	부모 윈도우 기반 윈도우 시작좌표 : x
					, ptClientWorld.y		//	부모 윈도우 기반 윈도우 시작좌표 : y
					, rc.right	- rc.left	//	윈도우 사이즈 : width
					, rc.bottom	- rc.top	//	윈도우 사이즈 : height
					, NULL					//	부모 윈도우.
					, NULL					//	메뉴 핸들
					, hInstance				//	인스턴스 핸들
					, NULL					//	추가 파라메터 : NULL
			);

		if (!g_Framework.OnCreate(hInstance, hWnd)) return(FALSE);
		//	생성 실패시 프로그램 종료
		//	확인 : WndProc의 default msg handler가 DefWindowProc 함수를 반환하는가?
		if (!hWnd)	return FALSE;

		//	윈도우 표시
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);

		//	성공 반환
		return TRUE;
	}

	//
	//  함수: MyRegisterClass()
	//
	//  목적: 창 클래스를 등록합니다.
	//
	ATOM MyRegisterClass(HINSTANCE hInstance)
	{
		WNDCLASSEX wcex;

		wcex.cbSize			= sizeof(WNDCLASSEX);
		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= szWindowClass;
		wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

		return RegisterClassEx(&wcex);
	}
};

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.
	MSG msg;

	wsprintf(szTitle, Win32TitleName);
	wsprintf(szWindowClass, TEXT("winMain"));

	// 전역 문자열을 초기화합니다.
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance(hInstance, nCmdShow)) return FALSE; 

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else g_Framework.FrameAdvance();
	}

	g_Framework.OnDestroy();

	return (int)msg.wParam;
}



//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDBLCLK:
	case WM_MOUSELEAVE:
	case WM_MBUTTONDOWN:
		g_Framework.OnProcessingMouseMessage(hWnd, message, wParam, lParam);
		break;

	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	case WM_IME_COMPOSITION:
	case WM_IME_STARTCOMPOSITION:
		g_Framework.OnProcessingKeyboardMessage(hWnd, message, wParam, lParam);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		g_Framework.PresentFrameBuffer(hdc);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		if (!g_Framework.OnProcessingWindowMessage(hWnd, message, wParam, lParam))
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}