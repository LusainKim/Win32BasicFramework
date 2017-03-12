//-----------------------------------------------------------------------------
// File: Scene.h
//-----------------------------------------------------------------------------

#pragma once

#include <windows.h>
#include <string>

class CFramework;

class CScene
{
public:

    CScene();
	virtual ~CScene();
	
	virtual bool OnProcessingKeyboardMessage	(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage		(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage		(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildObjects(std::wstring Tag, HWND hWnd, CFramework *pMasterFramework);
	virtual void ReleaseObjects();

	virtual void AnimateObjects(float fTimeElapsed);
	virtual void Draw(HDC hDC);

	bool FindByTag(std::wstring Tag);
	std::wstring GetTag() { return m_wsTag; }
protected:
	std::wstring					m_wsTag;
	HWND							m_hWnd;
	CFramework						*m_pMasterFramework;
};

