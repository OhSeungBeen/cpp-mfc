
// DATABASEDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDATABASEDlg ��ȭ ����
class CDATABASEDlg : public CDialog
{
// �����Դϴ�.
public:
	CDATABASEDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DATABASE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
