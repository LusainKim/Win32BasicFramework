//-----------------------------------------------------------------------------
// File: Scene.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Scene.h"
#include "Framework.h"

using namespace std;

CScene::CScene()
{

}

CScene::~CScene()
{
	ReleaseObjects();
}

bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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
		break;
	}

	return(false);
}

bool CScene::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	default:
		return false;
	}

	return false;
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		break;
	default:
		break;
	}
	return(false);
}

void CScene::BuildObjects(wstring Tag, HWND hWnd, CFramework *pMasterFramework)
{
	m_wsTag = Tag;
	m_hWnd = hWnd;
	m_pMasterFramework = pMasterFramework;
}

void CScene::ReleaseObjects()
{
}

void CScene::AnimateObjects(float fTimeElapsed)
{

}

void CScene::Draw(HDC hDC)
{

}

bool CScene::FindByTag(std::wstring Tag)
{
	return Tag == m_wsTag;
}
