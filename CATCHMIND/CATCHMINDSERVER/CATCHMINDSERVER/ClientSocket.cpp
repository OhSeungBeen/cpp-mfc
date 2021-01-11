// ClientSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CATCHMINDSERVER.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket(CObList * m_pClientSocketList)
{
	this->m_pClientSocketList = m_pClientSocketList;
	m_dataBase.Connect();
}

CClientSocket::~CClientSocket()
{
}

// �����͸� ������ ȣ��ȴ�.
void CClientSocket::OnReceive(int nErrorCode)
{
	
	int header[2];
	Receive((char*)header, sizeof(int) * 2);

	if(header[0] == JOIN) // ȸ�� ����
	{
		JoinInfo joinInfo;
		Receive((char*)&joinInfo, header[1]);
		int result = m_dataBase.InsertMember(joinInfo.name, joinInfo.id, joinInfo.pw, joinInfo.imagePath);

		if(result == 1) // ���� ����
			Send(&result, sizeof(int));
		else // ���� ����
			Send(&result, sizeof(int));
	}
	else if(header[0] == LOGIN) // �α���
	{
		LoginInfo loginInfo;
		Receive((char*)&loginInfo, header[1]);
		_RecordsetPtr pRecordSet = m_dataBase.SelectMember(loginInfo.id, loginInfo.pw);
		
		int result;
		if(pRecordSet != NULL && !pRecordSet->adoEOF)
		{
			FieldPtr pFld =  pRecordSet->Fields->GetItem(_variant_t("MemberName")); // ID, NAME ����
			_variant_t fldVal = pFld->GetValue();
			CString name = (LPCSTR)(_bstr_t)fldVal.bstrVal;

			strcpy_s(m_profileInfo.name, name);
			strcpy_s(m_profileInfo.id, loginInfo.id);
			
			result = 1;
			Send(&result, sizeof(int)); // ���� ����
			Send((char*)&m_profileInfo, sizeof(m_profileInfo)); // ������ ���� ����
		}
		else
		{
			result = 0; // ���� ����
			Send(&result, sizeof(int));
		}
	}
	else if(header[0] == FILE)
	{

		CFile file;
		file.Open("test.bmp", CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		byte* imageData = new byte[4096];
		DWORD dwRead;
		
		int fileSize = header[1];
		int receiveSize = 0;

		do{
			dwRead = Receive(imageData, 4096);
			file.Write(imageData, dwRead);
			receiveSize += dwRead;
			if(receiveSize >= fileSize)
				break;
		}while(dwRead > 0);

		delete imageData;
		file.Close();
	}
	
	CSocket::OnReceive(nErrorCode);
}


void CClientSocket::OnClose(int nErrorCode)
{

	CSocket::OnClose(nErrorCode);

	CClientSocket* p;
	POSITION pos = m_pClientSocketList->GetHeadPosition(), pre_pos;
	while (pos != NULL) {
		pre_pos = pos;
		p = (CClientSocket *)m_pClientSocketList->GetNext(pos);
		if (p == this) {
			m_pClientSocketList->RemoveAt(pre_pos);
			delete p;
		}
	}
}
