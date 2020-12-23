// CalculatorDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CALCULATOR.h"
#include "CALCULATORDlg.h"


// CCalculatorDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCALCULATORDlg, CDialog)

CCALCULATORDlg::CCALCULATORDlg(CWnd* pParent /*=NULL*/)
: CDialog(CCALCULATORDlg::IDD, pParent)
, m_strEditDisplay(_T(""))
, m_strEditHistory(_T(""))
, m_strStaticNo(_T(""))
{
	m_operatorButtonClick = false;
	m_equalButtonClick = false;
	
	CString strTemp;
	m_strStaticNo.Format("%p번지 계산기", this);
}

CCALCULATORDlg::~CCALCULATORDlg()
{
}

void CCALCULATORDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DISPLAY, m_strEditDisplay);
	DDX_Text(pDX, IDC_EDIT_HISTORY, m_strEditHistory);
	DDX_Text(pDX, IDC_STATIC_NO, m_strStaticNo);
}


BEGIN_MESSAGE_MAP(CCALCULATORDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ZERO, &CCALCULATORDlg::OnBnClickedButtonZero)
	ON_BN_CLICKED(IDC_BUTTON_ONE, &CCALCULATORDlg::OnBnClickedButtonOne)
	ON_BN_CLICKED(IDC_BUTTON_TWO, &CCALCULATORDlg::OnBnClickedButtonTwo)
	ON_BN_CLICKED(IDC_BUTTON_THREE, &CCALCULATORDlg::OnBnClickedButtonThree)
	ON_BN_CLICKED(IDC_BUTTON_FOUR, &CCALCULATORDlg::OnBnClickedButtonFour)
	ON_BN_CLICKED(IDC_BUTTON_FIVE, &CCALCULATORDlg::OnBnClickedButtonFive)
	ON_BN_CLICKED(IDC_BUTTON_SIX, &CCALCULATORDlg::OnBnClickedButtonSix)
	ON_BN_CLICKED(IDC_BUTTON_SEVEN, &CCALCULATORDlg::OnBnClickedButtonSeven)
	ON_BN_CLICKED(IDC_BUTTON_EIGHT, &CCALCULATORDlg::OnBnClickedButtonEight)
	ON_BN_CLICKED(IDC_BUTTON_NINE, &CCALCULATORDlg::OnBnClickedButtonNine)
	ON_BN_CLICKED(IDC_BUTTON_MULTIPLE, &CCALCULATORDlg::OnBnClickedButtonMultiple)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CCALCULATORDlg::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CCALCULATORDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_RESULT, &CCALCULATORDlg::OnBnClickedButtonResult)
	
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCALCULATORDlg::OnBnClickedButtonClear)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CCalculatorDlg 메시지 처리기입니다.

void CCALCULATORDlg::OnBnClickedButtonZero()
{
	ClickNumber("0");
}

void CCALCULATORDlg::OnBnClickedButtonOne()
{
	ClickNumber("1");
}

void CCALCULATORDlg::OnBnClickedButtonTwo()
{
	ClickNumber("2");
}

void CCALCULATORDlg::OnBnClickedButtonThree()
{
	ClickNumber("3");
}
void CCALCULATORDlg::OnBnClickedButtonFour()
{
	ClickNumber("4");
}

void CCALCULATORDlg::OnBnClickedButtonFive()
{
	ClickNumber("5");
}

void CCALCULATORDlg::OnBnClickedButtonSix()
{
	ClickNumber("6");
}

void CCALCULATORDlg::OnBnClickedButtonSeven()
{
	ClickNumber("7");
}

void CCALCULATORDlg::OnBnClickedButtonEight()
{
	ClickNumber("8");
}

void CCALCULATORDlg::OnBnClickedButtonNine()
{
	ClickNumber("9");
}

void CCALCULATORDlg::OnBnClickedButtonMultiple()
{
	ClickOperator('*');
}

void CCALCULATORDlg::OnBnClickedButtonMinus()
{
	ClickOperator('-');
}
void CCALCULATORDlg::OnBnClickedButtonPlus()
{
	ClickOperator('+');
}

void CCALCULATORDlg::OnBnClickedButtonResult()
{
	UpdateData();
	if(m_strEditDisplay.IsEmpty())
		return;

	Caculate();
	m_operatorButtonClick = false;
}

void CCALCULATORDlg::ClickNumber(CString number)
{
	if(m_strEditDisplay == "0")
		m_strEditDisplay.Empty();

	if(m_equalButtonClick)
	{
		m_strEditDisplay.Empty();
		m_equalButtonClick = false;
	}
	m_strEditDisplay += number;
	m_strEditHistory += number;
	UpdateData(FALSE);
}

void CCALCULATORDlg::ClickOperator(char op)
{
	if(m_strEditDisplay.IsEmpty())
		return;

	if(m_operatorButtonClick)
	{
		Caculate();
	}

	m_operatorButtonClick = true;
	m_operator = op;
	m_preOperand = m_strEditDisplay; 
	m_strEditHistory += op;
	UpdateData(FALSE);
	m_strEditDisplay.Empty();
}


void CCALCULATORDlg::Caculate()
{
	int preOperand = atoi(m_preOperand);
	int Operand = atoi(m_strEditDisplay);
	int result;

	switch(m_operator)
	{
		case '+':
			result = preOperand + Operand;
			break;
		case '-':
			result = preOperand - Operand;
			break;
		case '*':
			result = preOperand * Operand;
			break;
	}

	m_strEditDisplay.Format("%d", result);
	
	CString *message = new CString;
	message->Format("%s = %d", m_strEditHistory, result);
	HWND hWnd = ::FindWindow(NULL,"CALCULATOR_MONITOR");
	::SendMessage(hWnd,WM_USER_MESSAGE2, (WPARAM)this, (LPARAM)message);
	
	UpdateData(FALSE);
	m_equalButtonClick = true;
}
void CCALCULATORDlg::OnBnClickedButtonClear()
{
	m_preOperand.Empty();
	m_strEditDisplay.Empty();
	m_strEditHistory.Empty();
	
	m_equalButtonClick = false;
	m_operatorButtonClick = false;
	UpdateData(FALSE);
}

void CCALCULATORDlg::OnClose()
{
	::SendMessage(GetParent()->GetSafeHwnd(),WM_USER_MESSAGE, NULL, (LPARAM)this);
	CDialog::OnClose();
	delete this;
}
