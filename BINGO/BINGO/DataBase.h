#pragma once
#include "Data.h"
#include <vector>

class CDatabase
{
public:
	CDatabase(void);
	virtual ~CDatabase(void);

	_ConnectionPtr m_pConnection;
	HRESULT m_hr;
	BOOL m_isConnectionOpen;

	void Connect();
	int InsertMember(CString id, CString name, CString password);
	Member SelectMember(CString id, CString pw);
	std::vector<Member> SelectAllOhterMember(CString id);
	CString SelectRandomQuiz();
};

