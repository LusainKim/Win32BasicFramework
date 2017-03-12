// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <chrono>
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <memory>
#include <algorithm>
#include <random>
#include <fstream>

#include "Vector2D.h"
#include "scroll.h"

// imm32 ���� �۾��� �� �� �ʿ�
// #pragma comment(lib, "imm32")

#pragma comment(lib, "winmm")
#pragma comment(lib, "msimg32")

#include "Define.h"

extern HINSTANCE hInst;
inline float oneframe(float fps) { return ((fps == 0.f) ? -1.f : (1.f / float(fps))); }

template<typename Pt = D2D_POINT_2F> inline
POINT MakePoint(Pt pt) { POINT retpt; retpt.x = static_cast<LONG>(pt.x); retpt.y = static_cast<LONG>(pt.y); return retpt; }
template<typename _Ty = LONG> inline
POINT MakePoint(_Ty x, _Ty y) { POINT pt; pt.x = static_cast<LONG>(x); pt.y = static_cast<LONG>(y); return pt; }
template<typename Rect = D2D_RECT_F> inline
RECT MakeRect(Rect rc)
{
	RECT retrc;
	retrc.left = static_cast<LONG>(rc.left);
	retrc.top = static_cast<LONG>(rc.top);
	retrc.right = static_cast<LONG>(rc.right);
	retrc.bottom = static_cast<LONG>(rc.bottom);
	return retrc;
}
template<typename _Ty = LONG> inline
RECT MakeRect(_Ty left, _Ty top, _Ty right, _Ty bottom)
{
	RECT rc;
	rc.left = static_cast<LONG>(left);
	rc.top = static_cast<LONG>(top);
	rc.right = static_cast<LONG>(right);
	rc.bottom = static_cast<LONG>(bottom);
	return rc;
}

inline POINT operator+(POINT a, const POINT b) { return MakePoint(a.x + b.x, a.y + b.y); }
inline POINT operator-(POINT a, const POINT b) { return MakePoint(a.x - b.x, a.y - b.y); }
inline POINT operator*(float b, POINT a) { return MakePoint(a.x *b, a.y *b); }
inline bool operator==(POINT p1, POINT p2) { return (p1.x == p2.x && p1.y == p2.y) ? true : false; }
inline bool operator!=(POINT p1, POINT p2) { return (p1.x == p2.x && p1.y == p2.y) ? false : true; }

inline RECT operator+(RECT rc, POINT pt) { return MakeRect(pt.x + rc.left, pt.y + rc.top, pt.x + rc.right, pt.y + rc.bottom); }
inline RECT operator+(POINT pt, RECT rc) { return MakeRect(pt.x + rc.left, pt.y + rc.top, pt.x + rc.right, pt.y + rc.bottom); }
inline RECT operator+(RECT rc_1, RECT rc_2) { return MakeRect(rc_1.left + rc_2.left, rc_1.top + rc_2.top, rc_1.right + rc_2.right, rc_1.bottom + rc_2.bottom); }
