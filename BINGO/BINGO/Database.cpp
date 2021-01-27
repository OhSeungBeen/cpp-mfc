#include "StdAfx.h"
#include "DataBase.h"
#include "Data.h"

CDatabase::CDatabase(void)
{
	
}

CDatabase::~CDatabase(void)
{

}
void CDatabase::Connect()
{
	try
	{
		m_hr = m_pConnection.CreateInstance(__uuidof(Connection));
		CString dataBasePath;
		GetCurrentDirectory(_MAX_PATH, dataBasePath.GetBuffer(_MAX_PATH + 1));
		dataBasePath.ReleaseBuffer();
		dataBasePath += "\\database\\Bingo.mdb";
		CString connection = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + dataBasePath;
		m_pConnection->Open(_bstr_t(connection), "", "", adModeUnknown);
		if(SUCCEEDED(m_hr))
		{
			m_isConnectionOpen = TRUE;
		}
	}
	catch (_com_error &e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
};


int CDatabase::InsertMember(CString name, CString id, CString pw)
{
	try
	{
		if(SUCCEEDED(m_hr))
		{
			CString query = "INSERT INTO MEMBER(mId, mNickName, mPassword) VALUES('" +
				id + "','" + name + "','" + pw + "')";
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

Member CDatabase::SelectMember(CString id, CString pw)
{
	Member member = {};
	try
	{
		if(SUCCEEDED(m_hr))
		{
			CString query = "SELECT * FROM MEMBER WHERE mId='" + id + "' and mPassword='" + pw + "'";
			//AfxMessageBox(query);
			_RecordsetPtr pRecordSet = m_pConnection->Execute(_bstr_t(query), NULL, adCmdText);
			
			if(pRecordSet != NULL && !pRecordSet->adoEOF)
			{
				FieldPtr pFld =  pRecordSet->Fields->GetItem(_variant_t("mId")); // ID
				_variant_t fldVal = pFld->GetValue();
				CString id = (LPCSTR)(_bstr_t)fldVal.bstrVal;

				pFld = pRecordSet->Fields->GetItem(_variant_t("mNickName")); // NAME
				fldVal = pFld->GetValue();
				CString nickName = (LPCSTR)(_bstr_t)fldVal.bstrVal;
				
				member.valid = TRUE;
				strcpy_s(member.id, id);
				strcpy_s(member.nickName, nickName);
				return member;
			}
		}
		return member;
	}
	catch (_com_error &e)
	{
		AfxMessageBox(e.ErrorMessage());
		return member;
	}
}

std::vector<Member> CDatabase::SelectAllOhterMember(CString id)
{
	std::vector<Member> vMember;
	try
	{
		if(SUCCEEDED(m_hr))
		{
			Member member;
			CString query = "SELECT * FROM MEMBER WHERE mId NOT IN('" + id + "')";
			_RecordsetPtr pRecordSet = m_pConnection->Execute(_bstr_t(query), NULL, adCmdText);

			while(!(pRecordSet->adoEOF))
			{
				FieldPtr pFld =  pRecordSet->Fields->GetItem(_variant_t("mId")); // ID
				_variant_t fldVal = pFld->GetValue();
				CString id = (LPCSTR)(_bstr_t)fldVal.bstrVal;

				pFld = pRecordSet->Fields->GetItem(_variant_t("mNickName")); // NICK NAME
				fldVal = pFld->GetValue();
				CString name = (LPCSTR)(_bstr_t)fldVal.bstrVal;

				member.valid = TRUE;
				strcpy_s(member.id, id);
				strcpy_s(member.nickName, name);
				vMember.push_back(member);

				pRecordSet->MoveNext();
			}
		}
		return vMember;
	}
	catch (_com_error &e)
	{
		AfxMessageBox(e.ErrorMessage());
		return vMember;
	}
}


CString CDatabase::SelectRandomQuiz()
{
	CString quiz = "";
	try
	{
		if(SUCCEEDED(m_hr))
		{
			CString query = "SELECT top 1 Subject FROM BINGO ORDER BY Rnd(-(100000*ID)*Time())";
			_RecordsetPtr pRecordSet = m_pConnection->Execute(_bstr_t(query), NULL, adCmdText);

			FieldPtr pFld =  pRecordSet->Fields->GetItem(_variant_t("Subject")); // ID
			_variant_t fldVal = pFld->GetValue();
			quiz = (LPCSTR)(_bstr_t)fldVal.bstrVal;

			return quiz;
		}
		return quiz;
	}
	catch (_com_error &e)
	{
		AfxMessageBox(e.ErrorMessage());
		return quiz;
	}
}