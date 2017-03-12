//-----------------------------------------------------------------------------
// File: LobbyScene.h
//-----------------------------------------------------------------------------

#pragma once
#include "Scene.h"


class CLobbyScene 
	: public CScene
{

public:

	CLobbyScene();
	virtual ~CLobbyScene();
	
	virtual bool OnProcessingKeyboardMessage	(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) override;
	virtual bool OnProcessingMouseMessage		(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) override;
	virtual bool OnProcessingWindowMessage		(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) override;

	virtual void BuildObjects(std::wstring Tag, HWND hWnd, CFramework *pMasterFramework) override;
	virtual void ReleaseObjects() override;

	virtual void AnimateObjects(float fTimeElapsed) override;
	virtual void Draw(HDC hDC) override;

private:

};

