
// SERVER.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSERVERApp:
// �� Ŭ������ ������ ���ؼ��� SERVER.cpp�� �����Ͻʽÿ�.
//

class CSERVERApp : public CWinAppEx
{
public:
	CSERVERApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSERVERApp theApp;