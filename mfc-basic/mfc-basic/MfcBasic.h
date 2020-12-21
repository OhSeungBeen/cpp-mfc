
// mfc-basic.h : mfc-basic 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// CmfcbasicApp:
// 이 클래스의 구현에 대해서는 mfc-basic.cpp을 참조하십시오.
//

class CMFCBasic : public CWinApp
{
public:
	CMFCBasic();


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
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
