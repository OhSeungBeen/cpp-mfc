
// PAINT_PROJECT.h : PAINT_PROJECT ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CPAINT_PROJECTApp:
// �� Ŭ������ ������ ���ؼ��� PAINT_PROJECT.cpp�� �����Ͻʽÿ�.
//

class CPAINT_PROJECTApp : public CWinApp
{
public:
	CPAINT_PROJECTApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPAINT_PROJECTApp theApp;
