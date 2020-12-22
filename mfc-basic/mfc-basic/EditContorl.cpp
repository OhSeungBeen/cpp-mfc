// EditContorl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EditContorl.h"


// CEditContorl 대화 상자입니다.

IMPLEMENT_DYNAMIC(CEditContorl, CDialog)

CEditContorl::CEditContorl(CWnd* pParent /*=NULL*/)
	: CDialog(CEditContorl::IDD, pParent)
	, m_strEditId("ID") // 초기 값을 넣어줄 수 있다.
	, m_strEditPassword("PASSWORD")
{

}

CEditContorl::~CEditContorl()
{
}

void CEditContorl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	// DDX : Dialog Data eXchange
	// 컨트롤 윈도우와 멤버 변수와 연결
	DDX_Text(pDX, IDC_Edit_Id, m_strEditId);
	DDX_Text(pDX, IDC_Edit_Password, m_strEditPassword);

	// DDV : Dialog Data Validation 
	// 데이터의 유효성을 검사하는 함수
	// 12자 이내로 입력하십시오. 오류 메세지가 출력된다.
	DDV_MaxChars(pDX, m_strEditId, 12);
}


BEGIN_MESSAGE_MAP(CEditContorl, CDialog)
	ON_BN_CLICKED(ID_Button_Ok, &CEditContorl::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CEditContorl 메시지 처리기입니다.

void CEditContorl::OnBnClickedButtonOk()
{
	// 특정 변수와 컨트롤 윈도우 간에 정보 교환이 일어나도록 하는 함수
	BOOL result = UpdateData(TRUE); // 에디트 컨트롤 데이터 -> 에디트 컨트롤과 연결된 변수
	//UpdateData(FALSE); // 에디트 컨트롤과 연결된 변수 -> 에디트 컨트롤 데이터
	// 반환형 BOOL
	// 대부분 TRUE를 반환하지만 데이터의 유효성을 검사할 수 있도록 한경우 조건을
	// 만족하지못하면 FALSE를 반환한다.

	// 에디트 박스 내용 출력
	if (result) // 유효성검사가 통과되면 TRUE
	{
		CString strTemp;
		strTemp.Format("ID : %s \nPASSWORD : %s",m_strEditId, m_strEditPassword);
		AfxMessageBox(strTemp);
	}
}
