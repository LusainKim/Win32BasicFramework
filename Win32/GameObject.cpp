#include "stdafx.h"
#include "GameObject.h"

using namespace std;

CGameObject::CGameObject()
{
}

CGameObject::CGameObject(const Vec2f & pos)
	: CGameObject()
{
	SetPosition(pos);
}


CGameObject::~CGameObject()
{
}

void CGameObject::Draw(HDC hDC) const
{
	Ellipse(
		hDC	, m_ptPosition.x + m_rcSize.left
			, m_ptPosition.y + m_rcSize.top
			, m_ptPosition.x + m_rcSize.right
			, m_ptPosition.y + m_rcSize.bottom
	);
}

void CGameObject::Update(float fTimeElapsed)
{

}
