#pragma once


// CWordEdit

class CWordEdit : public CEdit
{
	DECLARE_DYNAMIC(CWordEdit)

public:
	CWordEdit();
	virtual ~CWordEdit();

protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL m_check;
	CBrush m_brBkgnd;
	COLORREF m_backgroundColor;

	void SetBkColor(COLORREF backgroundColor);
	void SetCheck(BOOL check);

	afx_msg HBRUSH CtlColor( CDC* pDC, UINT nCtlColor );
};

