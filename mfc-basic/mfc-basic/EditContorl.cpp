// EditContorl.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "EditContorl.h"


// CEditContorl ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CEditContorl, CDialog)

CEditContorl::CEditContorl(CWnd* pParent /*=NULL*/)
	: CDialog(CEditContorl::IDD, pParent)
	, m_strEditId("ID") // �ʱ� ���� �־��� �� �ִ�.
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
	// ��Ʈ�� ������� ��� ������ ����
	DDX_Text(pDX, IDC_Edit_Id, m_strEditId);
	DDX_Text(pDX, IDC_Edit_Password, m_strEditPassword);

	// DDV : Dialog Data Validation 
	// �������� ��ȿ���� �˻��ϴ� �Լ�
	// 12�� �̳��� �Է��Ͻʽÿ�. ���� �޼����� ��µȴ�.
	DDV_MaxChars(pDX, m_strEditId, 12);
}


BEGIN_MESSAGE_MAP(CEditContorl, CDialog)
	ON_BN_CLICKED(ID_Button_Ok, &CEditContorl::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CEditContorl �޽��� ó�����Դϴ�.

void CEditContorl::OnBnClickedButtonOk()
{
	// Ư�� ������ ��Ʈ�� ������ ���� ���� ��ȯ�� �Ͼ���� �ϴ� �Լ�
	BOOL result = UpdateData(TRUE); // ����Ʈ ��Ʈ�� ������ -> ����Ʈ ��Ʈ�Ѱ� ����� ����
	//UpdateData(FALSE); // ����Ʈ ��Ʈ�Ѱ� ����� ���� -> ����Ʈ ��Ʈ�� ������
	// ��ȯ�� BOOL
	// ��κ� TRUE�� ��ȯ������ �������� ��ȿ���� �˻��� �� �ֵ��� �Ѱ�� ������
	// �����������ϸ� FALSE�� ��ȯ�Ѵ�.

	// ����Ʈ �ڽ� ���� ���
	if (result) // ��ȿ���˻簡 ����Ǹ� TRUE
	{
		CString strTemp;
		strTemp.Format("ID : %s \nPASSWORD : %s",m_strEditId, m_strEditPassword);
		AfxMessageBox(strTemp);
	}
}
