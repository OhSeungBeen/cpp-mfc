#include "StdAfx.h"
#include "DataBase.h"

CDataBase::CDataBase(void)
{
	
}

CDataBase::~CDataBase(void)
{

}

void CDataBase::Connect()
{
	m_hr = m_pConnection.CreateInstance(__uuidof(Connection));
	CString dataBasePath;
	GetCurrentDirectory(_MAX_PATH, dataBasePath.GetBuffer(_MAX_PATH + 1));
	dataBasePath.ReleaseBuffer();
	dataBasePath += "\\Debug\\database\\CatchMind.mdb";
	CString connection = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + dataBasePath;
	m_pConnection->Open(_bstr_t(connection), "", "", adModeUnknown);

	if(SUCCEEDED(m_hr))
	{
		m_isConnectionOpen = TRUE;
	}
};


int CDataBase::InsertMember(CString name, CString id, CString pw, CString imagePath)
{
	try
	{
		if(SUCCEEDED(m_hr))
		{
			CString query = "INSERT INTO MEMBER(MemberName, MemberId, MemberPw, MemberImagePath) VALUES('" +
				name + "', '" + id + "', '" + pw + "', '" + imagePath + "')";
			m_pConnection->Execute(_bstr_t(query), NULL, adCmdText);
			return 1;
		}

		return 0;
	}
	catch (_com_error &e)
	{
		AfxMessageBox(e.ErrorMessage());
		return 0;
	}
}


_RecordsetPtr CDataBase::SelectMember(CString id, CString pw)
{
	try
	{
		if(SUCCEEDED(m_hr))
		{
			CString query = "SELECT * FROM MEMBER WHERE MemberId='" + id + "' and MemberPw='" + pw + "'";
			//AfxMessageBox(query);
			_RecordsetPtr pRecordSet = m_pConnection->Execute(_bstr_t(query), NULL, adCmdText);
			return pRecordSet;
		}
		return NULL;
	}
	catch (_com_error &e)
	{
		AfxMessageBox(e.ErrorMessage());
		return NULL;
	}
}


