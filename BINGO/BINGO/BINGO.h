
// CATCHMIND.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCATCHMINDApp:
// �� Ŭ������ ������ ���ؼ��� CATCHMIND.cpp�� �����Ͻʽÿ�.
//

class CBINGOApp : public CWinAppEx
{
public:
	CBINGOApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CBINGOApp theApp;