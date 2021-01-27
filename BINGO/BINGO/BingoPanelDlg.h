#pragma once
#include "afxwin.h"
#include "WordEdit.h"

// CBingoPanelDlg ��ȭ �����Դϴ�.

class CBingoPanelDlg : public CDialog
{
	DECLARE_DYNAMIC(CBingoPanelDlg)

public:
	CBingoPanelDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBingoPanelDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BINGO_PANEL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
public:
	CWordEdit **m_pEditWord;
	CStatic ctrl_staticNickName;

	int m_row;
	int m_col;

	CBrush m_brushEdit;
	int m_id;

	virtual BOOL OnInitDialog();

	void SetAllWordsEnbled(BOOL enAbled);
	void SetStaticNickName(CString nickName);
	BOOL CheckAllWordIsNull();
	CString GetAllWords();
	void SetAllWords(CString words);
	void SpliteStrToArray(CString strData, CString Seperator, CStringArray& arr);
	BOOL CheckWord(CString message, COLORREF rgb);
	void SetCheckedWordColor(COLORREF rgb);


	afx_msg void OnDestroy();
};
