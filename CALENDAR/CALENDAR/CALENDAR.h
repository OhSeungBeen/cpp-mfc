
// CALENDAR.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCALENDARApp:
// �� Ŭ������ ������ ���ؼ��� CALENDAR.cpp�� �����Ͻʽÿ�.
//

class CCALENDARApp : public CWinAppEx
{
public:
	CCALENDARApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCALENDARApp theApp;