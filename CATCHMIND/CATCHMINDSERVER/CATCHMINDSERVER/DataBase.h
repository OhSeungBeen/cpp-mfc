#pragma once

class CDataBase
{
public:
	CDataBase(void);
	virtual ~CDataBase(void);
	
	_ConnectionPtr m_pConnection;
	HRESULT m_hr;
	BOOL m_isConnectionOpen;

	void Connect();
	int InsertMember(CString name, CString id, CString pw, CString imagePath);
	_RecordsetPtr SelectMember(CString id, CString pw);

};
