// LoginDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CATCHMIND.h"
#include "CATCHMINDDlg.h"
#include "LoginDlg.h"
#include "JoinDlg.h"
#include "Global.h"

// CLoginDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
		
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDD_BTN_LOGIN, &CLoginDlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDD_BTN_JOIN, &CLoginDlg::OnBnClickedBtnJoin)
END_MESSAGE_MAP()


// CLoginDlg 메시지 처리기입니다.

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CFont fnt;
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 50;
	lf.lfWeight = FW_BOLD;
	::lstrcpy(lf.lfFaceName, "Tahoma");
	fnt.CreateFontIndirect(&lf);
	GetDlgItem(IDD_STATIC)->SetFont(&fnt);
	fnt.Detach();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

// 회원 가입
void CLoginDlg::OnBnClickedBtnJoin()
{
	CJoinDlg joinDlg;

	if(joinDlg.DoModal() == IDOK)
	{

		CString preImageName = joinDlg.m_file.GetFileName();
		CString ext = PathFindExtension(preImageName);
		CString imageName = CreateGuidString() + ext;
		CString imagePath = "profileImage\\" + imageName; 

		CFile file;
		CFile file2;
		byte* imageData = new byte[4096];
		DWORD dwRead;

		file.Open(imagePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		do{
			dwRead = joinDlg.m_file.Read(imageData, 4096);
			file.Write(imageData, dwRead); // profileImage\\ 이미지 저장
		}while(dwRead > 0);


		delete imageData;
		joinDlg.m_file.Close();

		// 데이터 베이스 저장
		int result = g_dataBase.InsertMember(joinDlg.m_name, joinDlg.m_id, joinDlg.m_pw, imageName);

		if(result)
		{
			AfxMessageBox("JOIN SUCESSS");
			g_logManager.Log("회원 가입");
		}
		else
		{
			AfxMessageBox("JOIN FAIL");
			g_logManager.Log("회원 가입 실패");
		}
	}
}

// 로그인 
void CLoginDlg::OnBnClickedBtnLogin()
{
	CString id, pw;
	GetDlgItemText(IDC_EDIT_LOGIN_ID, id);
	GetDlgItemText(IDC_EDIT_LOGIN_PW, pw);
	if(id.IsEmpty() || pw.IsEmpty())
	{
		AfxMessageBox("ID와 PASSWORD를 입력해 주세요.");
		return;
	}
	Member member = g_dataBase.SelectMember(id, pw);

	if(member.valid)
	{
		g_member = member;
		g_vMember = g_dataBase.SelectAllOhterMember(member.id);
		((CCATCHMINDDlg*)GetParent())->ChangeDlg(LOGIN_ROOM, WATING_ROOM);
		g_logManager.Log("로그인");
		//AfxMessageBox("LOGIN SUCCESS");
	}
	else
		AfxMessageBox("LOGIN FAIL");
}



// GUID 생성
CString CLoginDlg::CreateGuidString()
{
	GUID guid;
	wchar_t wszCLSID[129];
	CoCreateGuid(&guid);
	StringFromGUID2(guid, wszCLSID, 128);

	USES_CONVERSION;
	return OLE2A(wszCLSID);
}

