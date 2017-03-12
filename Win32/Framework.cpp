#include "stdafx.h"
#include "Framework.h"

#include "Scene.h"
#include "TitleScene.h"
#include "LobbyScene.h"

using namespace std;

CFramework::CFramework()
{
	lstrcpy(m_pszBuffer, Win32TitleName);

#ifdef _DEBUG
	lstrcat(m_pszBuffer, _T(" ("));
#endif
	
	m_nTitleLen = lstrlen(m_pszBuffer);
	m_hInstance = NULL;
	m_hWnd = NULL;
	m_hMenu = NULL;

	// DC & Bitmap
	m_hDCFrameBuffer = NULL;
	m_hBitmapFrameBuffer = NULL;
	m_hBitmapSelect = NULL;

	m_bBackgroundColor = 0x00FFFFFF;
	m_hbrBackground = NULL;

	// Viewport
	m_cxViewport = CLIENT_WIDTH;
	m_cyViewport = CLIENT_HEIGHT;

	// Timer
	m_cCurrentTime = chrono::system_clock::now();
	m_cLastUpdateTime = chrono::system_clock::now();
	m_fps = 0.f;

}

CFramework::~CFramework()
{
	OnDestroy();
}

bool CFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
	m_hInstance = hInstance;
	m_hWnd = hMainWnd;

	RECT rc;
	::GetClientRect(m_hWnd, &rc);
	m_xViewport = rc.left;
	m_yViewport = rc.top;
	m_cxViewport = rc.right - rc.left;
	m_cyViewport = rc.bottom - rc.top;

	BuildObjects();

	return(true);

}

void CFramework::OnDestroy()
{
	ReleaseObjects();
}

void CFramework::BuildFrameBuffer()
{
	HDC hDC = ::GetDC(m_hWnd);

	if (!m_hDCFrameBuffer) m_hDCFrameBuffer = ::CreateCompatibleDC(hDC);
	if (m_hBitmapFrameBuffer)
	{
		::SelectObject(m_hDCFrameBuffer, NULL);
		::DeleteObject(m_hBitmapFrameBuffer);
		m_hBitmapFrameBuffer = NULL;
	}

	m_hBitmapFrameBuffer = ::CreateCompatibleBitmap(hDC, m_cxViewport, m_cyViewport);
	::SelectObject(m_hDCFrameBuffer, m_hBitmapFrameBuffer);

	::ReleaseDC(m_hWnd, hDC);
	::SetBkMode(m_hDCFrameBuffer, TRANSPARENT);
	
	ChangeBackgroundBrush(m_bBackgroundColor);
}

void CFramework::ClearFrameBuffer()
{
	::FillRect(m_hDCFrameBuffer, &GetClientRect(), m_hbrBackground);
}

void CFramework::ChangeBackgroundBrush(DWORD dwColor)
{
	if (m_hbrBackground) ::DeleteObject(m_hbrBackground);
	m_hbrBackground = ::CreateSolidBrush(dwColor);
}

void CFramework::PresentFrameBuffer(HDC hDC)
{
	::BitBlt(hDC, m_xViewport, m_yViewport, m_cxViewport, m_cyViewport, m_hDCFrameBuffer, m_xViewport, m_yViewport, SRCCOPY);
}

void CFramework::BuildObjects()
{
	BuildFrameBuffer();

	m_lScene.push_back(make_unique<CTitleScene>());
	m_lScene.back()->BuildObjects(TEXT("Title"), m_hWnd, this);

	m_lScene.push_back(make_unique<CLobbyScene>());
	m_lScene.back()->BuildObjects(TEXT("Lobby"), m_hWnd, this);

	ChangeScene(TEXT("Title"));
}

void CFramework::ReleaseObjects()
{
	if (m_hbrBackground)		::DeleteObject(m_hbrBackground);
	if (m_hDCFrameBuffer)		::DeleteDC(m_hDCFrameBuffer);
	if (m_hBitmapFrameBuffer)	::DeleteObject(m_hBitmapFrameBuffer);
	if (m_hBitmapSelect)		::DeleteObject(m_hBitmapSelect);
}

bool CFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_CHAR:
		break;
		
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			::DestroyWindow(hWnd);
			::PostQuitMessage(0);
			return (true);
		}
		break;
	case WM_KEYUP:
		break;
	}
	
	return(m_pNowScene && m_pNowScene->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam));
}

bool CFramework::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (m_pNowScene && m_pNowScene->OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam)) return true;

	POINT mp = MousePoint(lParam);
	
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:

		m_bGrip = false;
		m_ptLast = mp;

		break;
	case WM_RBUTTONDOWN:

		break;
	case WM_MOUSEMOVE:
		if (m_bGrip)
		{
			m_ptLast = mp;
		}
		break;
	case WM_LBUTTONUP:

		m_bGrip = false;
		break;
	}
	
	return(true);
}

bool CFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	default:
		return false;
	}

	return(m_pNowScene && m_pNowScene->OnProcessingWindowMessage(hWnd, nMessageID, wParam, lParam));
}

POINT CFramework::MousePoint(LPARAM lParam)
{
//	static POINT Mp;
//	POINT pt = { -1, -1 };
//	if (LOWORD(lParam) == sideStore(0, (int)LOWORD(lParam), m_cxViewport))
//		pt.x = Mp.x = LOWORD(lParam);
//	if (HIWORD(lParam) == sideStore(0, (int)HIWORD(lParam), m_cyViewport))
//		pt.y = Mp.y = HIWORD(lParam);
//
//	if (MakePoint(-1, -1) == pt) pt = Mp;
//
//	return Mp;
	return{LOWORD(lParam), HIWORD(lParam)};
}

void CFramework::ChangeScene(wstring Tag, bool bDestroyPostScene)
{
	auto ChangeScene = find_if(m_lScene.begin(), m_lScene.end(),
		[=](const unique_ptr<CScene>& s) 
		{ return s->FindByTag(Tag); }
	);

	if (ChangeScene == m_lScene.end()) return _DEBUG_ERROR("생성되지 않은 Scene을 참조하려 했습니다!");

	if (m_pNowScene && bDestroyPostScene)
	{
		wstring DestroyTag = m_pNowScene->GetTag();

		m_pNowScene = nullptr;

		m_lScene.remove_if(
			[=](const unique_ptr<CScene>& s) 
			{return s->FindByTag(DestroyTag);}
		);
	}

	m_pNowScene = ChangeScene->get();
}


void CFramework::AnimateObjects(float fTimeElapsed)
{
	if (m_pNowScene) m_pNowScene->AnimateObjects(fTimeElapsed);
}

void CFramework::OnDraw()
{
	ClearFrameBuffer();

	if (m_pNowScene) m_pNowScene->Draw(m_hDCFrameBuffer);
}

void CFramework::FrameAdvance()
{

//	Calculate Tick ----------------------------------------------------------------------------

	m_cftimeElapsed = chrono::system_clock::now() - m_cCurrentTime;

#ifdef USE_LIMIT_FPS
	if (m_cftimeElapsed.count() > oneframe(LIMIT_FPS))
#else
	if (true)
#endif
	{
		m_cCurrentTime = chrono::system_clock::now();
		if (m_cftimeElapsed.count() > 0.f)
			m_fps = 1.f / m_cftimeElapsed.count();
	}
	else return;

//	-------------------------------------------------------------------------------------------

	AnimateObjects(static_cast<float>(m_cftimeElapsed.count()));
	OnDraw();

	::InvalidateRect(m_hWnd, NULL, FALSE);


//	Update Window -----------------------------------------------------------------------------

	m_cfUpdateElapsed = chrono::system_clock::now() - m_cLastUpdateTime;

	if (m_cfUpdateElapsed.count() > RENEWALWINTEXTCOUNT)
		m_cLastUpdateTime = chrono::system_clock::now();
	else return;

#ifdef _DEBUG
	::_itow_s(static_cast<int>(m_fps + 0.1f), m_pszBuffer + m_nTitleLen, TITLELENTH - m_nTitleLen, 10);
	::wcscat_s(m_pszBuffer + m_nTitleLen, TITLELENTH - m_nTitleLen, _T(" FPS)"));
#endif

	::SetWindowText(m_hWnd, m_pszBuffer);

//	-------------------------------------------------------------------------------------------
}
