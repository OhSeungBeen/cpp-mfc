
// mfc-basic.h : mfc-basic ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CmfcbasicApp:
// �� Ŭ������ ������ ���ؼ��� mfc-basic.cpp�� �����Ͻʽÿ�.
//

class CMFCBasic : public CWinApp
{
public:
	CMFCBasic();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
protected:
	HMENU  m_hMDIMenu;
	HACCEL m_hMDIAccel;

public:
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMenuThreadEx();
};

extern CMFCBasic theApp;
