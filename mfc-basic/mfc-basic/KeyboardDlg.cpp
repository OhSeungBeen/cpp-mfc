// KeyboardDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "KeyboardDlg.h"


// CKeyboardDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CKeyboardDlg, CDialog)

CKeyboardDlg::CKeyboardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyboardDlg::IDD, pParent)
{

}

CKeyboardDlg::~CKeyboardDlg()
{
}

void CKeyboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CKeyboardDlg, CDialog)
END_MESSAGE_MAP()


// CKeyboardDlg 메시지 처리기입니다.
