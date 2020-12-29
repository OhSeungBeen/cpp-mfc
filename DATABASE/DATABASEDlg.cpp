
// DATABASEDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "DATABASE.h"
#include "DATABASEDlg.h"
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CDATABASEDlg 대화 상자




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


// CDATABASEDlg 메시지 처리기

BOOL CDATABASEDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	
	ctrl_comboColType.AddString("TEXT");
	ctrl_comboColType.AddString("INTEGER");
	ctrl_comboColType.AddString("DATE");
	ctrl_comboColType.AddString("BIT");
	ctrl_comboColType.SetCurSel(0);
	
	ctrl_listTableDesign.InsertColumn(0, "컬럼명", LVCFMT_LEFT, 100);
	ctrl_listTableDesign.InsertColumn(1, "컬럼 타입", LVCFMT_CENTER, 100);
	
	try 
	{
		AfxGetModuleState()->m_dwVersion = 0x0601; //DAO (Access2000) 이후 버전 리딩가능
		AfxOleInit();// COM이나 OLE를 라이브러리를 초기화한다
		HRESULT hr = m_pConnection.CreateInstance(__uuidof(Connection));
		if (SUCCEEDED(hr))
		{
			CString connection = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\\Users\\seung\\Desktop\\DATABASE\\Debug\\Test.mdb";
			m_pConnection->Open(_bstr_t(connection), L"", L"",adModeUnknown);
		}

		if(SUCCEEDED(hr))
		{
			AfxMessageBox("데이터베이스 연결됨");
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
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDATABASEDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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
		AfxMessageBox("컬럼명을 입력해 주세요");
		return;
	}
	try{
		if(ctrl_checkSaveDatabase.GetCheck())
		{
			ctrl_listTable.GetText(ctrl_listTable.GetCurSel(), tableName);
			if(index == -1)
			{
				AfxMessageBox("테이블을 선택해 주세요.");
				return;
			}
			CString query = "ALTER TABLE " + tableName + " ADD " + colName + " " + colType;
			m_pConnection->Execute(_bstr_t(query), NULL, NULL);
			AfxMessageBox("query : " + query);
			AfxMessageBox( colName + "컬럼이 추가되었습니다.");			
		}
		ctrl_listTableDesign.InsertItem(itemCnt, colName);
		ctrl_listTableDesign.SetItemText(itemCnt, 1, colType);
	} catch(_com_error &e){
		AfxMessageBox(e.ErrorMessage()); // 데이터가 있을 경우 컬럼추가 에러
	}

}

void CDATABASEDlg::OnBnClickedBtnCreateTable()
{
	CString tableName;

	if(ctrl_listTableDesign.GetItemCount() == 0)
	{
		AfxMessageBox("컬럼이 없습니다.");
		return;
	}

	GetDlgItemText(IDC_EDIT_TABLE_NAME, tableName);
	if(tableName.IsEmpty())
	{
		AfxMessageBox("테이블명을 입력해 주세요.");
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
				AfxMessageBox(tableName + " 테이블을 생성 하였습니다.");
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
		AfxMessageBox("삭제할 컬럼을 선택해 주세요.");
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
			AfxMessageBox( colName + "컬럼이 삭제되었습니다.");
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
		// 컬럼만 가져오기 위한 쿼리문
		CString query = "SELECT * FROM " + tableName + " WHERE 1 = 0"; 
		_RecordsetPtr pRecordset = m_pConnection->Execute(_bstr_t(query), NULL, adCmdText);
		int fieldCnt = pRecordset->GetFields()->Count;
		_variant_t vIndex;
		
		ctrl_listTableDesign.DeleteAllItems();
		while(ctrl_listTableView.DeleteColumn(0)); // 전체 컬럼 삭제

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
	// 테이블 조회
	// 컬럼만 가져오기 위한 쿼리문
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
		AfxMessageBox("테이블을 선택해 주세요.");
		return;
	}

	ctrl_listTable.GetText(index, tableName);
	CString query = "DROP TABLE " + tableName;
	if(m_pConnection)
	{
		try{
			m_pConnection->Execute(_bstr_t(query), NULL, NULL);
			AfxMessageBox("query : " + query);
			AfxMessageBox(tableName + " 테이블을 삭제 하였습니다.");

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
		AfxMessageBox("테이블을 선택해 주세요.");
		return;
	}

	index = ctrl_listTableDesign.GetNextItem( -1, LVNI_SELECTED );
	if(index == -1)
	{
		AfxMessageBox("복제할 컬럼을 선택해 주세요.");
		return;
	}

	colName = ctrl_listTableDesign.GetItemText(index, 0);
	colType = ctrl_listTableDesign.GetItemText(index, 1);
	GetDlgItemText(IDC_EDIT_COL_NAME, copyColName);
	if(copyColName.IsEmpty())
	{
		AfxMessageBox("복제할 컬럼명을 입력해 주세요.");
		return;
	}
	if(copyColName == colName)
	{
		AfxMessageBox("복사할 컬럼이름과 같을 수 없습니다.");
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
			AfxMessageBox( colName + "컬럼이 추가되었습니다.");			
		}
		ctrl_listTableDesign.InsertItem(itemCnt, copyColName);
		ctrl_listTableDesign.SetItemText(itemCnt, 1, colType);
	} catch(_com_error &e){
		AfxMessageBox(e.ErrorMessage()); // 데이터가 있을 경우 컬럼 복제 에러
	}
}

void CDATABASEDlg::OnBnClickedBtnColCovertType()
{
	CString tableName, colName, colType, convertColType;

	int index = ctrl_listTable.GetCurSel();
	if(index == -1 && ctrl_checkSaveDatabase.GetCheck())
	{
		AfxMessageBox("테이블을 선택해 주세요.");
		return;
	}

	index = ctrl_listTableDesign.GetNextItem( -1, LVNI_SELECTED );
	if(index == -1)
	{
		AfxMessageBox("타입을 변경 할 컬럼을 선택해 주세요.");
		return;
	}

	colName = ctrl_listTableDesign.GetItemText(index, 0);
	colType = ctrl_listTableDesign.GetItemText(index, 1);
	GetDlgItemText(IDC_EDIT_COL_TYPE, convertColType);
	if(convertColType == colType)
	{
		AfxMessageBox("변경할 컬럼타입과 같을 수 없습니다.");
		return;
	}

	try{
		if(ctrl_checkSaveDatabase.GetCheck())
		{
			ctrl_listTable.GetText(ctrl_listTable.GetCurSel(), tableName);
			CString query = "ALTER TABLE " + tableName + " ALTER COLUMN " + colName + " " + convertColType;
			*m_pConnection->Execute(_bstr_t(query), NULL, NULL);
			AfxMessageBox("query : " + query);
			AfxMessageBox( colName + "컬럼 타입이 변경되었습니다.");
		}

		ctrl_listTableDesign.SetItemText(index, 1, convertColType);
	} catch(_com_error &e){
		AfxMessageBox(e.ErrorMessage()); // 데이터가 있을 경우 컬럼 형변환 에러
	}
}

void CDATABASEDlg::OnDestroy()
{
	CDialog::OnDestroy();

	m_pConnection->Close(); // connection 메모리 해제
}