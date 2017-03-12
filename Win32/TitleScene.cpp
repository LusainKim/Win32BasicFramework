#include "stdafx.h"
#include "Framework.h"
#include "TitleScene.h"

using namespace std;

CTitleScene::CTitleScene()
{
}

CTitleScene::~CTitleScene()
{
	ReleaseObjects();
}

bool CTitleScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
		m_pMasterFramework->ChangeBackgroundBrush(RGB(255, 255, 255));
		m_pMasterFramework->ChangeScene(TEXT("Lobby"), true);
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

bool CTitleScene::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	default:
		return false;
	}

	return false;
}

bool CTitleScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

void CTitleScene::BuildObjects(wstring Tag, HWND hWnd, CFramework *pMasterFramework)
{
	CScene::BuildObjects(Tag, hWnd, pMasterFramework);
}

void CTitleScene::ReleaseObjects()
{
}

void CTitleScene::AnimateObjects(float fTimeElapsed)
{
}

void CTitleScene::Draw(HDC hDC)
{
	auto str = L"클릭하면 다음 Scene으로 넘어갑니다. Lobby Scene에 작업해주세요."s;
	TextOut(hDC, 100, 100, str.c_str(), str.length());
}
