
// DATABASE.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CDATABASEApp:
// �� Ŭ������ ������ ���ؼ��� DATABASE.cpp�� �����Ͻʽÿ�.
//

class CDATABASEApp : public CWinAppEx
{
public:
	CDATABASEApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CDATABASEApp theApp;