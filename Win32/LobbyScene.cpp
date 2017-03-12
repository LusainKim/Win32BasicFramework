#include "stdafx.h"
#include "Framework.h"
#include "GameObject.h"
#include "LobbyScene.h"

using namespace std;

CLobbyScene::CLobbyScene()
{
}


CLobbyScene::~CLobbyScene()
{
	ReleaseObjects();
}

bool CLobbyScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONUP:
		break;
	default:
		return true;
	}

	return(false);
}

bool CLobbyScene::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	default:
		return true;
	}

	return false;
}

bool CLobbyScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		
		default:
			break;
		}
		break;
	default:
		return true;
	}
	return(false);
}

void CLobbyScene::BuildObjects(wstring Tag, HWND hWnd, CFramework *pMasterFramework)
{
	CScene::BuildObjects(Tag, hWnd, pMasterFramework);

}

void CLobbyScene::ReleaseObjects()
{
}

void CLobbyScene::AnimateObjects(float fTimeElapsed)
{
}

void CLobbyScene::Draw(HDC hDC)
{
}
