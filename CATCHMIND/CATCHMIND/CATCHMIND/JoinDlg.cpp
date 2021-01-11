// JoinDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CATCHMIND.h"
#include "JoinDlg.h"


// CJoinDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CJoinDlg, CDialog)

CJoinDlg::CJoinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJoinDlg::IDD, pParent)
{

}

CJoinDlg::~CJoinDlg()
{
}

void CJoinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CJoinDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CJoinDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CJoinDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_FILE, &CJoinDlg::OnBnClickedBtnFile)
END_MESSAGE_MAP()


// 회원 가입 버튼
void CJoinDlg::OnBnClickedOk()
{
	CString name, id, pw;
	GetDlgItemText(IDC_EDIT_JOIN_NAME, name);
	GetDlgItemText(IDC_EDIT_JOIN_ID, id);
	GetDlgItemText(IDC_EDIT_JOIN_PW, pw);
	if(id.IsEmpty() || pw.IsEmpty() || name.IsEmpty())
	{
		AfxMessageBox("필수(NAME, ID, PASSWORD)를 입력해 주세요.");
		return;
	}

	m_name = name;
	m_id = id;
	m_pw = pw;
	OnOK();
}

// 취소 버튼
void CJoinDlg::OnBnClickedCancel()
{
	OnCancel();
}

void CJoinDlg::OnBnClickedBtnFile()
{
	char filter[] = "Files(*.jpg, *.bmp)|*.jpg;*.bmp; |All Files(*.*)|*.*||";
	CFileDialog cFileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter);
	if(IDOK == cFileDlg.DoModal())
	{
		CString filePath = cFileDlg.GetPathName();
		try
		{
			m_file.Open((LPCTSTR)filePath, CFile::modeRead | CFile::typeBinary);
		} catch(CFileException e){
			e.ReportError();
		}
	}

}
