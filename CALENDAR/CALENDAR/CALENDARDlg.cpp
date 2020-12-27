
// CALENDARDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "CALENDAR.h"
#include "CALENDARDlg.h"
#include "MemoData.h"
#include "MemoInputDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCALENDARDlg 대화 상자


CCALENDARDlg::CCALENDARDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCALENDARDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pWndShow = NULL;
}

void CCALENDARDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MONTHCALENDAR, ctrl_monthCal);
	DDX_Control(pDX, IDC_TAB, ctrl_tab);
}

BEGIN_MESSAGE_MAP(CCALENDARDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR, &CCALENDARDlg::OnMcnSelchangeMonthcalendar)
	ON_BN_CLICKED(IDC_BTN_MEMO_ADD, &CCALENDARDlg::OnBnClickedBtnMemoAdd)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CCALENDARDlg::OnTcnSelchangeTab)
	ON_BN_CLICKED(IDC_BTN_MEMO_DELETE, &CCALENDARDlg::OnBnClickedBtnMemoDelete)
END_MESSAGE_MAP()


// CCALENDARDlg 메시지 처리기

BOOL CCALENDARDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	InitTabContorl();
	InitListContorl();

	m_date = GetDateString();
	SetDlgItemText(IDC_STATIC, m_date);
		
	m_pThread = AfxBeginThread(aramCheckThread, this);
	hThread = m_pThread->m_hThread;
	if(!m_pThread)
	{
		AfxMessageBox("스레드를 생성할 수 없습니다.");
		return TRUE;
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCALENDARDlg::InitListContorl()
{
	m_tabOneDlg.ctrl_listMemo.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_tabTwoDlg.ctrl_listMemo.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_tabThreeDlg.ctrl_listMemo.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_tabFourDlg.ctrl_listMemo.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_tabFiveDlg.ctrl_listMemo.SetExtendedStyle(LVS_EX_GRIDLINES);

	m_tabOneDlg.ctrl_listMemo.InsertColumn(0, "작성일", LVCFMT_LEFT, 80);
	m_tabOneDlg.ctrl_listMemo.InsertColumn(1, "내용", LVCFMT_LEFT, 200);
	m_tabOneDlg.ctrl_listMemo.InsertColumn(2, "알람시간", LVCFMT_LEFT, 80);
	
	m_tabTwoDlg.ctrl_listMemo.InsertColumn(0, "작성일", LVCFMT_LEFT, 80);
	m_tabTwoDlg.ctrl_listMemo.InsertColumn(1, "내용", LVCFMT_LEFT, 200);
	m_tabTwoDlg.ctrl_listMemo.InsertColumn(2, "알람시간", LVCFMT_LEFT, 80);

	m_tabThreeDlg.ctrl_listMemo.InsertColumn(0, "작성일", LVCFMT_LEFT, 80);
	m_tabThreeDlg.ctrl_listMemo.InsertColumn(1, "내용", LVCFMT_LEFT, 200);
	m_tabThreeDlg.ctrl_listMemo.InsertColumn(2, "알람시간", LVCFMT_LEFT, 80);

	m_tabFourDlg.ctrl_listMemo.InsertColumn(0, "작성일", LVCFMT_LEFT, 80);
	m_tabFourDlg.ctrl_listMemo.InsertColumn(1, "내용", LVCFMT_LEFT, 200);
	m_tabFourDlg.ctrl_listMemo.InsertColumn(2, "알람시간", LVCFMT_LEFT, 80);

	m_tabFiveDlg.ctrl_listMemo.InsertColumn(0, "작성일", LVCFMT_LEFT, 80);
	m_tabFiveDlg.ctrl_listMemo.InsertColumn(1, "내용", LVCFMT_LEFT, 200);
	m_tabFiveDlg.ctrl_listMemo.InsertColumn(2, "알람시간", LVCFMT_LEFT, 80);
}

void CCALENDARDlg::InitTabContorl()
{
	ctrl_tab.InsertItem(1, "Part1");
	ctrl_tab.InsertItem(2, "Part2");
	ctrl_tab.InsertItem(3, "Part3");
	ctrl_tab.InsertItem(4, "Part4");
	ctrl_tab.InsertItem(5, "Part5");
	CTapOneDlg* dlg1 = new CTapOneDlg;
	CTapOneDlg* dlg2 = new CTapOneDlg;
	CRect rect;
	ctrl_tab.GetClientRect(&rect);
	m_tabOneDlg.Create(IDD_TAP_DIALOG1, &ctrl_tab);
	m_tabOneDlg.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_pWndShow = &m_tabOneDlg;

	m_tabTwoDlg.Create(IDD_TAP_DIALOG2, &ctrl_tab);
	m_tabTwoDlg.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_NOZORDER);

	m_tabThreeDlg.Create(IDD_TAP_DIALOG3, &ctrl_tab);
	m_tabThreeDlg.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_NOZORDER);

	m_tabFourDlg.Create(IDD_TAP_DIALOG4, &ctrl_tab);
	m_tabFourDlg.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_NOZORDER);

	m_tabFiveDlg.Create(IDD_TAP_DIALOG5, &ctrl_tab);
	m_tabFiveDlg.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_NOZORDER);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCALENDARDlg::OnPaint()
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
HCURSOR CCALENDARDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CCALENDARDlg::GetTimeString()
{
	
	CTime cTime = CTime::GetCurrentTime();
	CString strTemp;
	strTemp.Format("%02d:%02d:%02d", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());

	return strTemp;
}

CString CCALENDARDlg::GetDateString()
{
	SYSTEMTIME time;
	ctrl_monthCal.GetCurSel(&time);
	CString strTemp;
	char* week[7] = { "일", "월", "화", "수", "목", "금", "토" };
	strTemp.Format("%4d-%2d-%2d-%s", time.wYear, time.wMonth, time.wDay, week[time.wDayOfWeek]);

	return strTemp;
}


void CCALENDARDlg::OnMcnSelchangeMonthcalendar(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	
	RemoveAllTabListItem();
	ctrl_tab.SetCurSel(0);
	
	m_date = GetDateString();
	SetDlgItemText(IDC_STATIC, m_date);
	
	if(m_pMemoDataList.GetCount() == 0)
		return;

	POSITION pos = m_pMemoDataList.GetHeadPosition();
	while(pos != NULL)
	{
		CMemoData* memoData = (CMemoData*)m_pMemoDataList.GetNext(pos);
		if(memoData->m_date == m_date)
		{
			int tabNo = memoData->m_tabNo;
			AddListItem(tabNo, memoData->m_content, memoData->m_aram);
		}
	}
	*pResult = 0;
}

void CCALENDARDlg::RemoveAllTabListItem()
{
	m_tabOneDlg.ctrl_listMemo.DeleteAllItems();
	m_tabTwoDlg.ctrl_listMemo.DeleteAllItems();
	m_tabThreeDlg.ctrl_listMemo.DeleteAllItems();
	m_tabFourDlg.ctrl_listMemo.DeleteAllItems();
	m_tabFiveDlg.ctrl_listMemo.DeleteAllItems();
}



void CCALENDARDlg::OnBnClickedBtnMemoAdd()
{
	CMemoInputDlg memoInputDlg;
	memoInputDlg.DoModal();

	if(memoInputDlg.m_content.IsEmpty())
		return;
	
	CMemoData* p_MemoData = new CMemoData;
	p_MemoData->m_date = m_date;
	p_MemoData->m_content = memoInputDlg.m_content;
	p_MemoData->m_tabNo = ctrl_tab.GetCurSel();
	p_MemoData->m_aram = memoInputDlg.m_time;
	m_pMemoDataList.AddTail(p_MemoData);
	
	AddListItem(ctrl_tab.GetCurSel(), memoInputDlg.m_content, memoInputDlg.m_time);
}

void CCALENDARDlg::AddListItem(int tabNo, CString content, CString aram)
{
	switch(tabNo)
	{
	case 0:
		{
			int itemCount = m_tabOneDlg.ctrl_listMemo.GetItemCount();
			m_tabOneDlg.ctrl_listMemo.InsertItem(itemCount, m_date);
			m_tabOneDlg.ctrl_listMemo.SetItem(itemCount, 1, LVIF_TEXT, content, 0, 0, 0, NULL);
			m_tabOneDlg.ctrl_listMemo.SetItem(itemCount, 2, LVIF_TEXT, aram, 0, 0, 0, NULL);
			break;
		}		
	case 1:
		{
			int itemCount = m_tabTwoDlg.ctrl_listMemo.GetItemCount();
			m_tabTwoDlg.ctrl_listMemo.InsertItem(itemCount, m_date);
			m_tabTwoDlg.ctrl_listMemo.SetItem(itemCount, 1, LVIF_TEXT, content, 0, 0, 0, NULL);
			m_tabTwoDlg.ctrl_listMemo.SetItem(itemCount, 2, LVIF_TEXT, aram, 0, 0, 0, NULL);
			break;
		}	
	case 2:
		{
			int itemCount = m_tabThreeDlg.ctrl_listMemo.GetItemCount();
			m_tabThreeDlg.ctrl_listMemo.InsertItem(itemCount, m_date);
			m_tabThreeDlg.ctrl_listMemo.SetItem(itemCount, 1, LVIF_TEXT, content, 0, 0, 0, NULL);
			m_tabThreeDlg.ctrl_listMemo.SetItem(itemCount, 2, LVIF_TEXT, aram, 0, 0, 0, NULL);
			break;
		}	
	case 3:
		{
			int itemCount = m_tabFourDlg.ctrl_listMemo.GetItemCount();
			m_tabFourDlg.ctrl_listMemo.InsertItem(itemCount, m_date);
			m_tabFourDlg.ctrl_listMemo.SetItem(itemCount, 1, LVIF_TEXT, content, 0, 0, 0, NULL);
			m_tabFourDlg.ctrl_listMemo.SetItem(itemCount, 2, LVIF_TEXT, aram, 0, 0, 0, NULL);
			break;
		}	
	case 4:
		{
			int itemCount = m_tabFiveDlg.ctrl_listMemo.GetItemCount();
			m_tabFiveDlg.ctrl_listMemo.InsertItem(itemCount, m_date);
			m_tabFiveDlg.ctrl_listMemo.SetItem(itemCount, 1, LVIF_TEXT, content, 0, 0, 0, NULL);
			m_tabFiveDlg.ctrl_listMemo.SetItem(itemCount, 2, LVIF_TEXT, aram, 0, 0, 0, NULL);
			break;
		}	
	}
}

void CCALENDARDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(m_pWndShow != NULL)
	{
		m_pWndShow->ShowWindow(SW_HIDE);
		m_pWndShow = NULL;
	}

	int index = ctrl_tab.GetCurSel();

	switch(index)
	{
		case 0:
			{
				m_tabOneDlg.ShowWindow(SW_SHOW);
				m_pWndShow = &m_tabOneDlg;
				break;
			}
		case 1:
			{
				m_tabTwoDlg.ShowWindow(SW_SHOW);
				m_pWndShow = &m_tabTwoDlg;
				break;
			}
		case 2:
			{
				m_tabThreeDlg.ShowWindow(SW_SHOW);
				m_pWndShow = &m_tabThreeDlg;
				break;
			}
		case 3:
			{
				m_tabFourDlg.ShowWindow(SW_SHOW);
				m_pWndShow = &m_tabFourDlg;
				break;
			}
		case 4:
			{
				m_tabFiveDlg.ShowWindow(SW_SHOW);
				m_pWndShow = &m_tabFiveDlg;
				break;
			}
	}
	*pResult = 0;
}

void CCALENDARDlg::OnBnClickedBtnMemoDelete()
{	
	int index = ctrl_tab.GetCurSel();

	CString content;
	CString date;

	switch(index)
	{
	case 0:
		{
			int selectedIndex = m_tabOneDlg.ctrl_listMemo.GetSelectionMark();
			date = m_tabOneDlg.ctrl_listMemo.GetItemText(selectedIndex, 0);
			content = m_tabOneDlg.ctrl_listMemo.GetItemText(selectedIndex, 1);
			m_tabOneDlg.ctrl_listMemo.DeleteItem(selectedIndex);
			break;
		}
	case 1:
		{
			int selectedIndex = m_tabTwoDlg.ctrl_listMemo.GetSelectionMark();
			date = m_tabTwoDlg.ctrl_listMemo.GetItemText(selectedIndex, 0);
			content = m_tabTwoDlg.ctrl_listMemo.GetItemText(selectedIndex, 1);
			m_tabTwoDlg.ctrl_listMemo.DeleteItem(selectedIndex);
			break;
		}
	case 2:
		{
			int selectedIndex = m_tabThreeDlg.ctrl_listMemo.GetSelectionMark();
			date = m_tabThreeDlg.ctrl_listMemo.GetItemText(selectedIndex, 0);
			content = m_tabThreeDlg.ctrl_listMemo.GetItemText(selectedIndex, 1);
			m_tabThreeDlg.ctrl_listMemo.DeleteItem(selectedIndex);
			break;
		}
	case 3:
		{
			int selectedIndex = m_tabFourDlg.ctrl_listMemo.GetSelectionMark();
			date = m_tabFourDlg.ctrl_listMemo.GetItemText(selectedIndex, 0);
			content = m_tabFourDlg.ctrl_listMemo.GetItemText(selectedIndex, 1);
			m_tabFourDlg.ctrl_listMemo.DeleteItem(selectedIndex);
			break;
		}
	case 4:
		{
			int selectedIndex = m_tabFiveDlg.ctrl_listMemo.GetSelectionMark();
			date = m_tabFiveDlg.ctrl_listMemo.GetItemText(index, 0);
			content = m_tabFiveDlg.ctrl_listMemo.GetItemText(index, 1);
			m_tabFiveDlg.ctrl_listMemo.DeleteItem(selectedIndex);
			break;
		}
	}

	POSITION pos = m_pMemoDataList.GetHeadPosition();
	while(pos != NULL)
	{
		CMemoData* memoData = (CMemoData*)m_pMemoDataList.GetNext(pos);

		if(memoData->m_date == date && memoData->m_content == content)
		{
			POSITION removePos = m_pMemoDataList.Find(memoData);
			m_pMemoDataList.RemoveAt(removePos);
		}
	}
}

UINT CCALENDARDlg::aramCheckThread( LPVOID pParam )
{
	CCALENDARDlg* pCalendarDlg = (CCALENDARDlg*)pParam;
	while(1)
	{
		CTime cTime = CTime::GetCurrentTime();
		CString time;
		time.Format("%02d:%02d:%02d", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
		
		POSITION pos = pCalendarDlg->m_pMemoDataList.GetHeadPosition();
		while(pos != NULL)
		{
			CMemoData* memoData = (CMemoData*)pCalendarDlg->m_pMemoDataList.GetNext(pos);

			if(memoData->m_aram == time)
			{
				CString strTemp;
				strTemp.Format("[알람 : %s] %s",time, memoData->m_content);
				AfxMessageBox(strTemp);
			}
		}
	
		
		Sleep(10);
	}
}