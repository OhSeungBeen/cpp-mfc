
// DATABASEDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "DATABASE.h"
#include "DATABASEDlg.h"
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDATABASEDlg ��ȭ ����




CDATABASEDlg::CDATABASEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDATABASEDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDATABASEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COL_TYPE, ctrl_comboColType);
	DDX_Control(pDX, IDC_LIST_TABLE_DESIGN, ctrl_listTableDesign);
	DDX_Control(pDX, IDC_LIST_TABLE, ctrl_listTable);
	DDX_Control(pDX, IDC_CHECK_SAVE_DATABASE, ctrl_checkSaveDatabase);
	DDX_Control(pDX, IDC_LIST_TABLE_VIEW, ctrl_listTableView);
}

BEGIN_MESSAGE_MAP(CDATABASEDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_COL_ADD, &CDATABASEDlg::OnBnClickedBtnColAdd)
	ON_BN_CLICKED(IDC_BTN_CREATE_TABLE, &CDATABASEDlg::OnBnClickedBtnCreateTable)
	ON_BN_CLICKED(IDC_BTN_COL_REMOVE, &CDATABASEDlg::OnBnClickedBtnColRemove)
	ON_LBN_SELCHANGE(IDC_LIST_TABLE, &CDATABASEDlg::OnLbnSelchangeListTable)
	ON_BN_CLICKED(IDC_BTN_DROP_TABLE, &CDATABASEDlg::OnBnClickedBtnDropTable)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_USER_QUERY_EXE, &CDATABASEDlg::OnBnClickedBtnUserQueryExe)
	ON_BN_CLICKED(IDC_BTN_COL_COPY, &CDATABASEDlg::OnBnClickedBtnColCopy)
	ON_BN_CLICKED(IDC_BTN_COL_COVERT_TYPE, &CDATABASEDlg::OnBnClickedBtnColCovertType)
END_MESSAGE_MAP()


// CDATABASEDlg �޽��� ó����

BOOL CDATABASEDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	
	ctrl_comboColType.AddString("TEXT");
	ctrl_comboColType.AddString("INTEGER");
	ctrl_comboColType.AddString("DATE");
	ctrl_comboColType.AddString("BIT");
	ctrl_comboColType.SetCurSel(0);
	
	ctrl_listTableDesign.InsertColumn(0, "�÷���", LVCFMT_LEFT, 100);
	ctrl_listTableDesign.InsertColumn(1, "�÷� Ÿ��", LVCFMT_CENTER, 100);
	
	try 
	{
		AfxGetModuleState()->m_dwVersion = 0x0601; //DAO (Access2000) ���� ���� ��������
		AfxOleInit();// COM�̳� OLE�� ���̺귯���� �ʱ�ȭ�Ѵ�
		HRESULT hr = m_pConnection.CreateInstance(__uuidof(Connection));
		if (SUCCEEDED(hr))
		{
			CString connection = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\\Users\\seung\\Desktop\\DATABASE\\Debug\\Test.mdb";
			m_pConnection->Open(_bstr_t(connection), L"", L"",adModeUnknown);
		}

		if(SUCCEEDED(hr))
		{
			AfxMessageBox("�����ͺ��̽� �����");
			m_isConnectionOpen = TRUE;
		}

		if(m_isConnectionOpen)
		{
			_RecordsetPtr pRstSchema;
			pRstSchema = m_pConnection->OpenSchema(adSchemaTables);
			while(!(pRstSchema->adoEOF))
			{
				_bstr_t tableType = pRstSchema->Fields->GetItem("TABLE_TYPE")->Value; 

				if(tableType != _bstr_t("ACCESS TABLE") && tableType != _bstr_t("SYSTEM TABLE") )
				{
					_bstr_t tableName = pRstSchema->Fields->GetItem("TABLE_NAME")->Value;
					ctrl_listTable.AddString(tableName);
				}
				pRstSchema->MoveNext();
			}
		}
	} catch(_com_error &e) 
	{
		AfxMessageBox(e.ErrorMessage());
	}
	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CDATABASEDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CDATABASEDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CDATABASEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDATABASEDlg::OnBnClickedBtnColAdd()
{
	CString tableName, colName, colType;

	int index = ctrl_listTable.GetCurSel();
	
	GetDlgItemText(IDC_EDIT_COL_NAME, colName);
	GetDlgItemText(IDC_EDIT_COL_TYPE, colType);
	int itemCnt = ctrl_listTableDesign.GetItemCount();

	if(colName.IsEmpty())
	{
		AfxMessageBox("�÷����� �Է��� �ּ���");
		return;
	}
	try{
		if(ctrl_checkSaveDatabase.GetCheck())
		{
			ctrl_listTable.GetText(ctrl_listTable.GetCurSel(), tableName);
			if(index == -1)
			{
				AfxMessageBox("���̺��� ������ �ּ���.");
				return;
			}
			CString query = "ALTER TABLE " + tableName + " ADD " + colName + " " + colType;
			m_pConnection->Execute(_bstr_t(query), NULL, NULL);
			AfxMessageBox("query : " + query);
			AfxMessageBox( colName + "�÷��� �߰��Ǿ����ϴ�.");			
		}
		ctrl_listTableDesign.InsertItem(itemCnt, colName);
		ctrl_listTableDesign.SetItemText(itemCnt, 1, colType);
	} catch(_com_error &e){
		AfxMessageBox(e.ErrorMessage()); // �����Ͱ� ���� ��� �÷��߰� ����
	}

}

void CDATABASEDlg::OnBnClickedBtnCreateTable()
{
	CString tableName;

	if(ctrl_listTableDesign.GetItemCount() == 0)
	{
		AfxMessageBox("�÷��� �����ϴ�.");
		return;
	}

	GetDlgItemText(IDC_EDIT_TABLE_NAME, tableName);
	if(tableName.IsEmpty())
	{
		AfxMessageBox("���̺���� �Է��� �ּ���.");
		return;
	}
	
	CString query;
	query += "CREATE TABLE " + tableName + "(";

	int itemCnt = ctrl_listTableDesign.GetItemCount();
	for(int i = 0; i < itemCnt; i++)
	{
		CString colName = ctrl_listTableDesign.GetItemText(i, 0);
		CString colType = ctrl_listTableDesign.GetItemText(i, 1);
		if(i == itemCnt - 1)
		{
			query += colName + " " + colType;
			continue;
		}
		query += colName + " " + colType + ",";
	}
	query += ")";
	AfxMessageBox("query : " + query);

	if(m_isConnectionOpen)
	{
		try{
			int result = m_pConnection->Execute(_bstr_t(query), NULL, NULL);
			if(result)
			{
				AfxMessageBox(tableName + " ���̺��� ���� �Ͽ����ϴ�.");
				ctrl_listTable.AddString(tableName);
			}
		}catch(_com_error &e){
			AfxMessageBox(e.ErrorMessage());
		}
		
	}
}

void CDATABASEDlg::OnBnClickedBtnColRemove()
{
	CString tableName, colName;
	
	int index = ctrl_listTableDesign.GetNextItem( -1, LVNI_SELECTED );
	if(index == -1)
	{
		AfxMessageBox("������ �÷��� ������ �ּ���.");
		return;
	}

	if(ctrl_checkSaveDatabase.GetCheck())
	{
		if(m_isConnectionOpen)
		{
			ctrl_listTable.GetText(ctrl_listTable.GetCurSel(), tableName);
			colName = ctrl_listTableDesign.GetItemText(index, 0);
			CString query = "ALTER TABLE " + tableName + " DROP COLUMN " + colName;
			m_pConnection->Execute(_bstr_t(query), NULL, NULL);
			AfxMessageBox("query : " + query);
			AfxMessageBox( colName + "�÷��� �����Ǿ����ϴ�.");
		}
	}
	ctrl_listTableDesign.DeleteItem(index);
}

void CDATABASEDlg::OnLbnSelchangeListTable()
{
	int index = ctrl_listTable.GetCurSel();
	CString tableName;
	ctrl_listTable.GetText(index, tableName);
	
	if(m_isConnectionOpen)
	{	
		// �÷��� �������� ���� ������
		CString query = "SELECT * FROM " + tableName + " WHERE 1 = 0"; 
		_RecordsetPtr pRecordset = m_pConnection->Execute(_bstr_t(query), NULL, adCmdText);
		int fieldCnt = pRecordset->GetFields()->Count;
		_variant_t vIndex;
		
		ctrl_listTableDesign.DeleteAllItems();
		while(ctrl_listTableView.DeleteColumn(0)); // ��ü �÷� ����

		for(short i = 0; i < fieldCnt; i++)
		{
			vIndex = i;
			FieldPtr pfield = pRecordset->Fields->GetItem(&vIndex);
			//AfxMessageBox(pfield->GetName());
			ctrl_listTableDesign.InsertItem(i, pfield->GetName());
			ctrl_listTableView.InsertColumn(i, pfield->GetName(), LVCFMT_LEFT, 50);
			int type = pfield->GetType(); 

			/*CString strTemp;
			strTemp.Format("%d", type);
			AfxMessageBox(strTemp);*/

			switch(type) 
			{
				case (adInteger): // INTEGER
					ctrl_listTableDesign.SetItemText(i, 1, "INTEGER");
					break;  
				case (adLongVarWChar): // TEXT
					ctrl_listTableDesign.SetItemText(i, 1, "TEXT");
					break;  
				 case (adDate): // DATE
					ctrl_listTableDesign.SetItemText(i, 1, "DATE");
					break;  
				 case (adBoolean): // BIT
					ctrl_listTableDesign.SetItemText(i, 1, "BIT");
					break;  
				 default:
					ctrl_listTableDesign.SetItemText(i, 1, "?");
					break;
			}  
		}

		selectTable(tableName);
	}
}

void CDATABASEDlg::selectTable(CString tableName)
{
	// ���̺� ��ȸ
	// �÷��� �������� ���� ������
	CString query = "SELECT * FROM " + tableName + " WHERE 1 = 0"; 

	ctrl_listTableView.DeleteAllItems();
	query = "SELECT * FROM " + tableName;
	_RecordsetPtr pRecordSet = m_pConnection->Execute(_bstr_t(query), NULL, NULL);

	int rowCnt = 0;
	while(!pRecordSet->adoEOF)
	{

		int colMax = ctrl_listTableView.GetHeaderCtrl()->GetItemCount();
		for(int colCnt = 0; colCnt < colMax; colCnt++)
		{
			CString colName = ctrl_listTableDesign.GetItemText(colCnt, 0);

			FieldPtr pFld = pRecordSet->Fields->GetItem(_variant_t(colName));
			_variant_t fldVal = pFld->GetValue();

			time_t time;
			struct tm timeinfo;

			CString strTemp;
			switch(fldVal.vt) 
			{  
			case (VT_BOOL): // BIT
				if (fldVal.boolVal)  
					strTemp = "TRUE";
				else  
					strTemp = "FALSE";  

				if(colCnt == 0)
					ctrl_listTableView.InsertItem(rowCnt, strTemp);
				else
					ctrl_listTableView.SetItemText(rowCnt, colCnt, strTemp);
				break;  
			case (VT_BSTR): // TEXT
				strTemp.Format("%s",(LPCSTR)(_bstr_t)fldVal.bstrVal);
				if(colCnt == 0)
					ctrl_listTableView.InsertItem(rowCnt, strTemp);
				else
					ctrl_listTableView.SetItemText(rowCnt, colCnt, strTemp);
				break;  
			case (VT_I4): // INTEGER
				strTemp.Format("%d",(LPCSTR)fldVal.iVal);
				if(colCnt == 0)
					ctrl_listTableView.InsertItem(rowCnt, strTemp);
				else
					ctrl_listTableView.SetItemText(rowCnt, colCnt, strTemp);
				break;  
			case (VT_EMPTY):
				strTemp.Format("%s",(LPCSTR)fldVal.iVal);
				if(colCnt == 0)
					ctrl_listTableView.InsertItem(rowCnt, strTemp);
				else
					ctrl_listTableView.SetItemText(rowCnt, colCnt, strTemp);
				break;
			case (VT_DATE): 
				time = (time_t)(DATE)fldVal.date;

				localtime_s(&timeinfo, &time);
				char date_string[100];
				strftime(date_string, 50,"%B %d %Y",&timeinfo);
				//strTemp.Format("%B %d %Y",&timeinfo);
				if(colCnt == 0)
					ctrl_listTableView.InsertItem(rowCnt, date_string);
				else
					ctrl_listTableView.SetItemText(rowCnt, colCnt, date_string);
				break;  
			default:
				if(colCnt == 0)
					ctrl_listTableView.InsertItem(rowCnt, "?");
				else
					ctrl_listTableView.SetItemText(rowCnt, colCnt, "?");
				break;  
			} 
		} // col
		pRecordSet->MoveNext();
		rowCnt++;
	} // row

}

void CDATABASEDlg::OnBnClickedBtnDropTable()
{
	CString tableName;

	int index = ctrl_listTable.GetCurSel();
	if(index == -1)
	{
		AfxMessageBox("���̺��� ������ �ּ���.");
		return;
	}

	ctrl_listTable.GetText(index, tableName);
	CString query = "DROP TABLE " + tableName;
	if(m_pConnection)
	{
		try{
			m_pConnection->Execute(_bstr_t(query), NULL, NULL);
			AfxMessageBox("query : " + query);
			AfxMessageBox(tableName + " ���̺��� ���� �Ͽ����ϴ�.");

			ctrl_listTable.DeleteString(index);
			ctrl_listTableDesign.DeleteAllItems();
			ctrl_listTableView.DeleteAllItems();
			while(ctrl_listTableView.DeleteColumn(0));
		}catch(_com_error e){
			AfxMessageBox(e.ErrorMessage());
		}
		
	}
}

void CDATABASEDlg::OnBnClickedBtnUserQueryExe()
{
	CString query;
	GetDlgItemText(IDC_EDIT_USER_QUERY, query);

	if(m_isConnectionOpen)
	{
		try{
			m_pConnection->Execute(_bstr_t(query), NULL, NULL);
			AfxMessageBox(query);
			int index = ctrl_listTable.GetCurSel();
			CString tableName;
			ctrl_listTable.GetText(index, tableName);
			selectTable(tableName); // refresh;
		}
		catch (_com_error &e){
			AfxMessageBox(e.ErrorMessage());
		}
		
	}
}

void CDATABASEDlg::OnBnClickedBtnColCopy()
{
	CString tableName, colName, colType, copyColName;

	int index = ctrl_listTable.GetCurSel();
	if(index == -1 && ctrl_checkSaveDatabase.GetCheck())
	{
		AfxMessageBox("���̺��� ������ �ּ���.");
		return;
	}

	index = ctrl_listTableDesign.GetNextItem( -1, LVNI_SELECTED );
	if(index == -1)
	{
		AfxMessageBox("������ �÷��� ������ �ּ���.");
		return;
	}

	colName = ctrl_listTableDesign.GetItemText(index, 0);
	colType = ctrl_listTableDesign.GetItemText(index, 1);
	GetDlgItemText(IDC_EDIT_COL_NAME, copyColName);
	if(copyColName.IsEmpty())
	{
		AfxMessageBox("������ �÷����� �Է��� �ּ���.");
		return;
	}
	if(copyColName == colName)
	{
		AfxMessageBox("������ �÷��̸��� ���� �� �����ϴ�.");
		return;
	}

	int itemCnt = ctrl_listTableDesign.GetItemCount();
	try{
		if(ctrl_checkSaveDatabase.GetCheck())
		{
			ctrl_listTable.GetText(ctrl_listTable.GetCurSel(), tableName);
			CString query = "ALTER TABLE " + tableName + " ADD " + copyColName + " " + colType;
			m_pConnection->Execute(_bstr_t(query), NULL, NULL);
			AfxMessageBox("query : " + query);
			AfxMessageBox( colName + "�÷��� �߰��Ǿ����ϴ�.");			
		}
		ctrl_listTableDesign.InsertItem(itemCnt, copyColName);
		ctrl_listTableDesign.SetItemText(itemCnt, 1, colType);
	} catch(_com_error &e){
		AfxMessageBox(e.ErrorMessage()); // �����Ͱ� ���� ��� �÷� ���� ����
	}
}

void CDATABASEDlg::OnBnClickedBtnColCovertType()
{
	CString tableName, colName, colType, convertColType;

	int index = ctrl_listTable.GetCurSel();
	if(index == -1 && ctrl_checkSaveDatabase.GetCheck())
	{
		AfxMessageBox("���̺��� ������ �ּ���.");
		return;
	}

	index = ctrl_listTableDesign.GetNextItem( -1, LVNI_SELECTED );
	if(index == -1)
	{
		AfxMessageBox("Ÿ���� ���� �� �÷��� ������ �ּ���.");
		return;
	}

	colName = ctrl_listTableDesign.GetItemText(index, 0);
	colType = ctrl_listTableDesign.GetItemText(index, 1);
	GetDlgItemText(IDC_EDIT_COL_TYPE, convertColType);
	if(convertColType == colType)
	{
		AfxMessageBox("������ �÷�Ÿ�԰� ���� �� �����ϴ�.");
		return;
	}

	try{
		if(ctrl_checkSaveDatabase.GetCheck())
		{
			ctrl_listTable.GetText(ctrl_listTable.GetCurSel(), tableName);
			CString query = "ALTER TABLE " + tableName + " ALTER COLUMN " + colName + " " + convertColType;
			*m_pConnection->Execute(_bstr_t(query), NULL, NULL);
			AfxMessageBox("query : " + query);
			AfxMessageBox( colName + "�÷� Ÿ���� ����Ǿ����ϴ�.");
		}

		ctrl_listTableDesign.SetItemText(index, 1, convertColType);
	} catch(_com_error &e){
		AfxMessageBox(e.ErrorMessage()); // �����Ͱ� ���� ��� �÷� ����ȯ ����
	}
}

void CDATABASEDlg::OnDestroy()
{
	CDialog::OnDestroy();

	m_pConnection->Close(); // connection �޸� ����
}