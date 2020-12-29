
// DATABASEDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDATABASEDlg 대화 상자
class CDATABASEDlg : public CDialog
{
// 생성입니다.
public:
	CDATABASEDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DATABASE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	_ConnectionPtr m_pConnection;
	bool m_isConnectionOpen;

	CComboBox ctrl_comboColType;
	CListCtrl ctrl_listTableDesign;
	CListBox ctrl_listTable;
	CButton ctrl_checkSaveDatabase;
	CListCtrl ctrl_listTableView;

	afx_msg void OnBnClickedBtnColAdd();
	afx_msg void OnBnClickedBtnCreateTable();
	afx_msg void OnBnClickedBtnColRemove();
	afx_msg void OnLbnSelchangeListTable();
	afx_msg void OnBnClickedBtnDropTable();
	afx_msg void OnBnClickedBtnUserQueryExe();
	afx_msg void OnDestroy();	
	afx_msg void OnBnClickedBtnColCopy();
	afx_msg void OnBnClickedBtnColCovertType();

	void selectTable(CString tableName);
};
