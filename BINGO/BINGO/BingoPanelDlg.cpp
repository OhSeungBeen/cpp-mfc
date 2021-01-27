// BingoPanelDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BINGO.h"
#include "BingoPanelDlg.h"

// CBingoPanelDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBingoPanelDlg, CDialog)

CBingoPanelDlg::CBingoPanelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBingoPanelDlg::IDD, pParent)
{
	m_row = 4;
	m_col = 4;
}

CBingoPanelDlg::~CBingoPanelDlg()
{
}

void CBingoPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NICKNAME, ctrl_staticNickName);
}


BEGIN_MESSAGE_MAP(CBingoPanelDlg, CDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


void CBingoPanelDlg::SetAllWordsEnbled(BOOL enAbled)
{
	for(int i = 0; i < m_row; i++)
	{
		for(int j = 0; j < m_col; j++)
		{
			m_pEditWord[i * m_col + j]->EnableWindow(enAbled);
		}
	}
}

void CBingoPanelDlg::SetAllWords(CString words)
{
	CStringArray wordsArray;
	SpliteStrToArray(words, "$", wordsArray);
	
	for(int i = 0; i < m_row; i++)
	{
		for(int j = 0; j < m_col; j++)
		{
			m_pEditWord[i * m_col + j]->SetWindowText(wordsArray[i * m_col + j]);
		}
	}
}

void CBingoPanelDlg::SpliteStrToArray(CString str, CString Seperator, CStringArray& arr)
{
	int Position = 0;
	CString Token;
	Token = str.Tokenize(Seperator, Position);
	if( Token != "") arr.Add(Token);
	while(!Token.IsEmpty())
	{
		Token = str.Tokenize(Seperator, Position);
		if(Token != "")
		{
			arr.Add(Token);
		}                                         
	}
}

CString CBingoPanelDlg::GetAllWords()
{
	CString word, words;
	for(int i = 0; i < m_row; i++)
	{
		for(int j = 0; j < m_col; j++)
		{
			m_pEditWord[i * m_col + j]->GetWindowText(word);
			words += word + '$';
		}
	}
	return words;
}

BOOL CBingoPanelDlg::CheckAllWordIsNull()
{
	CString strTemp;
	for(int i = 0; i < m_row; i++)
	{
		for(int j = 0; j < m_col; j++)
		{
			m_pEditWord[i * m_col + j]->GetWindowText(strTemp);
			if(strTemp.IsEmpty())
				return TRUE;
		}
	}
	return FALSE;
}

void CBingoPanelDlg::SetCheckedWordColor(COLORREF rgb)
{
	for(int i = 0; i < m_row; i++)
	{
		for(int j = 0; j < m_col; j++)
		{
			if(m_pEditWord[i * m_col + j]->m_check)
			{
				m_pEditWord[i * m_col + j]->SetBkColor(rgb);
				m_pEditWord[i * m_col + j]->ShowWindow(TRUE);
			}
		}
	}
}

BOOL CBingoPanelDlg::CheckWord(CString message, COLORREF rgb)
{
	CString strTemp;
	BOOL check = FALSE;
	for(int i = 0; i < m_row; i++)
	{
		for(int j = 0; j < m_col; j++)
		{
			m_pEditWord[i * m_col + j]->GetWindowText(strTemp);
			if(strTemp == message)
			{
				m_pEditWord[i * m_col + j]->SetCheck(TRUE);
				m_pEditWord[i * m_col + j]->SetBkColor(rgb);
				check = TRUE;
			}
		}
	}
	return check;
}

void CBingoPanelDlg::SetStaticNickName(CString nickName)
{
	ctrl_staticNickName.SetWindowText(nickName);
}

BOOL CBingoPanelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pEditWord = new CWordEdit *[m_row * m_col];
	for(int i = 0; i < m_row; i++)
	{
		for(int j = 0; j < m_col; j++)
		{
			m_pEditWord[i * m_col + j] = new CWordEdit();
			m_pEditWord[i * m_col + j]->CreateEx(WS_EX_CLIENTEDGE,
				"EDIT", "", WS_CHILD | WS_VISIBLE | WS_DISABLED,
				CRect(j * 85 + 20, i * 48 + 25, (j+1) * 85 , (i+1) * 48), this, 20000 + i * m_col + j);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CBingoPanelDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// delete memory
	for(int i = 0; i < m_row; i++)
	{
		for(int j = 0; j < m_col; j++)
		{
			delete m_pEditWord[i * m_col + j];
		}
	}
	delete[] m_pEditWord;
}

