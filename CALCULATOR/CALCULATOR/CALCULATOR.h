
// CALCULATOR.h : CALCULATOR ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CCALCULATORApp:
// �� Ŭ������ ������ ���ؼ��� CALCULATOR.cpp�� �����Ͻʽÿ�.
//

class CCALCULATORApp : public CWinApp
{
public:
	CCALCULATORApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCALCULATORApp theApp;
