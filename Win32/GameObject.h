#pragma once

enum class Direction
{
	  left
	, up
	, right
	, down
};

class CGameObject
{

public:
	CGameObject();
	CGameObject(const Vec2f& pos);
	~CGameObject();

	void SetPosition(const Vec2f& pos) { m_ptPosition = pos; }
	const Vec2f& GetPosition() const { return m_ptPosition; }

	virtual void Draw(HDC hDC) const;
	virtual void Update(float fTimeElapsed);

	RECT GetBoundingBox() const { return m_rcSize + m_ptPosition; }

protected:
	
	Vec2f			m_ptPosition;
	RECT			m_rcSize;
};
