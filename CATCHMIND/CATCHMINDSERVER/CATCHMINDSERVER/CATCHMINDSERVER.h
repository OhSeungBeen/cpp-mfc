
// CATCHMINDSERVER.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCATCHMINDSERVERApp:
// �� Ŭ������ ������ ���ؼ��� CATCHMINDSERVER.cpp�� �����Ͻʽÿ�.
//

class CCATCHMINDSERVERApp : public CWinAppEx
{
public:
	CCATCHMINDSERVERApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCATCHMINDSERVERApp theApp;