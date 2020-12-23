#pragma once


// CCalculatorDlg ��ȭ �����Դϴ�.

class CCALCULATORDlg : public CDialog
{
	DECLARE_DYNAMIC(CCALCULATORDlg)

public:
	CCALCULATORDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCALCULATORDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CALCULATOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonZero();
	afx_msg void OnBnClickedButtonOne();
	afx_msg void OnBnClickedButtonTwo();
	afx_msg void OnBnClickedButtonThree();
	afx_msg void OnBnClickedButtonFour();
	afx_msg void OnBnClickedButtonFive();
	afx_msg void OnBnClickedButtonSix();
	afx_msg void OnBnClickedButtonSeven();
	afx_msg void OnBnClickedButtonEight();
	afx_msg void OnBnClickedButtonNine();
	afx_msg void OnBnClickedButtonMultiple();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonResult();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnClose();

	void ClickNumber(CString number);
	void ClickOperator(char op);
	void Caculate();
	
	CString m_strEditDisplay;
	CString m_preOperand;
	CString m_strEditHistory;

	char m_operator;

	bool m_operatorButtonClick;
	bool m_equalButtonClick;
	CString m_strStaticNo;
};
