
// CLIENT.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCLIENTApp:
// �� Ŭ������ ������ ���ؼ��� CLIENT.cpp�� �����Ͻʽÿ�.
//

class CCLIENTApp : public CWinAppEx
{
public:
	CCLIENTApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCLIENTApp theApp;