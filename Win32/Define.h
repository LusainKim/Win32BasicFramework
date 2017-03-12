#pragma once

constexpr int CLIENT_WIDTH	= 800  ;
constexpr int CLIENT_HEIGHT	= 600 ;

constexpr int BlockSize = 20;

#define Win32TitleName TEXT("Win32API Program")

// �ִ� ������ ���� ����
#define USE_LIMIT_FPS
#define LIMIT_FPS 60.f
#define RENEWALWINTEXTCOUNT 0.5f
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

//������������������������������������������������
//				Font Define
//������������������������������������������������

#define FontSet_Arial 0,0,0,700,FALSE,FALSE,0,\
			DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,\
			DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS, TEXT("Arial")

#define FontSet_Arial_B 0,0,0,1000,FALSE,FALSE,0,\
			DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,\
			DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS, TEXT("Arial")

#define FontSet_Arial_L 0,0,0,1000,FALSE,FALSE,0,\
			DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,\
			DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS, TEXT("Arial")

//=============================

#define RandomColor (rand() % 0x80 + 0x80) * 0x100 * 0x100 + (rand() % 0x80 + 0x80) * 0x100 + (rand() % 0x80 + 0x100)

