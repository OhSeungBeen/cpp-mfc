#pragma once
#include "afxwin.h"
#include "WordEdit.h"

// CBingoPanelDlg 대화 상자입니다.

class CBingoPanelDlg : public CDialog
{
	DECLARE_DYNAMIC(CBingoPanelDlg)

public:
	CBingoPanelDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBingoPanelDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BINGO_PANEL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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
