#pragma once

class CMemoData
{
public:
	CMemoData(void);
	virtual ~CMemoData(void);

public:
	CString m_date;
	int m_tabNo;
	CString m_content;
	CString m_aram;
};
