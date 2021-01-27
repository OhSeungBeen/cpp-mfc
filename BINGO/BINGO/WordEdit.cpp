// WordEdit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BINGO.h"
#include "WordEdit.h"


// CWordEdit

IMPLEMENT_DYNAMIC(CWordEdit, CEdit)

CWordEdit::CWordEdit()
{
	m_check = false;
}

CWordEdit::~CWordEdit()
{
}


BEGIN_MESSAGE_MAP(CWordEdit, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()


void CWordEdit::SetCheck(BOOL check)
{
	m_check = check;
}

void CWordEdit::SetBkColor(COLORREF backgroundColor)
{
	m_backgroundColor = backgroundColor;
	m_brBkgnd.DeleteObject();
	m_brBkgnd.CreateSolidBrush(backgroundColor);
	Invalidate();
}

HBRUSH CWordEdit::CtlColor(CDC* pDC, UINT nCtlColor)
{
	if(m_check)
	{
		pDC->SetBkColor(m_backgroundColor);
		return CreateSolidBrush(m_backgroundColor);
	}
}
