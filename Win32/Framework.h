#pragma once

class CScene;

#define TITLELENTH 50

class CFramework
{
public:
	CFramework();
	~CFramework();

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

	void AnimateObjects(float fTimeElapsed);
	void FrameAdvance();
	void OnDraw();

	void BuildObjects();
	void ReleaseObjects();

	void BuildFrameBuffer();
	void ClearFrameBuffer();
	void ChangeBackgroundBrush(DWORD dwColor);
	void PresentFrameBuffer(HDC hDC);

	bool OnProcessingKeyboardMessage	(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingMouseMessage		(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingWindowMessage		(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	POINT MousePoint(LPARAM lParam);
	POINT GetCenterPosition(){ return{ m_cxViewport / 2, m_cyViewport / 2 }; }
	RECT GetClientRect() const { return RECT{ m_xViewport, m_yViewport, m_cxViewport, m_cyViewport }; }
	void ChangeScene(std::wstring Tag, bool bDestroyPostScene = false);

private:

	// Title
	_TCHAR									m_pszBuffer[TITLELENTH];
	int										m_nTitleLen;

	// GameTimer
	std::chrono::system_clock::time_point	m_cCurrentTime;
	std::chrono::duration<double>			m_cftimeElapsed;
	std::chrono::system_clock::time_point	m_cLastUpdateTime;
	std::chrono::duration<double>			m_cfUpdateElapsed;
	double									m_fps;

	// windows handle
	HINSTANCE								m_hInstance;
	HWND									m_hWnd;
	HMENU									m_hMenu;
	
	// Render Bitmap
	HDC										m_hDCFrameBuffer;
	HBITMAP									m_hBitmapFrameBuffer;
	HBITMAP									m_hBitmapSelect;

	DWORD									m_bBackgroundColor;
	HBRUSH									m_hbrBackground;

	// Viewport
	int										m_xViewport;
	int										m_yViewport;
	int										m_cxViewport;
	int										m_cyViewport;

	// Mouse Cursor
	bool									m_bGrip;
	POINT									m_ptLast;

	// Scene
	std::list<std::unique_ptr<CScene>> 		m_lScene;
	CScene									*m_pNowScene;
};

