
// SERIAL_COM.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSERIAL_COMApp:
// �� Ŭ������ ������ ���ؼ��� SERIAL_COM.cpp�� �����Ͻʽÿ�.
//

class CSERIAL_COMApp : public CWinAppEx
{
public:
	CSERIAL_COMApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSERIAL_COMApp theApp;