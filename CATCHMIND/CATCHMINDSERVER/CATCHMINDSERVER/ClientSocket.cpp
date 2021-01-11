// ClientSocket.cpp : 구현 파일입니다.
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

// 데이터를 받을때 호출된다.
void CClientSocket::OnReceive(int nErrorCode)
{
	
	int header[2];
	Receive((char*)header, sizeof(int) * 2);

	if(header[0] == JOIN) // 회원 가입
	{
		JoinInfo joinInfo;
		Receive((char*)&joinInfo, header[1]);
		int result = m_dataBase.InsertMember(joinInfo.name, joinInfo.id, joinInfo.pw, joinInfo.imagePath);

		if(result == 1) // 성공 전송
			Send(&result, sizeof(int));
		else // 실패 전송
			Send(&result, sizeof(int));
	}
	else if(header[0] == LOGIN) // 로그인
	{
		LoginInfo loginInfo;
		Receive((char*)&loginInfo, header[1]);
		_RecordsetPtr pRecordSet = m_dataBase.SelectMember(loginInfo.id, loginInfo.pw);
		
		int result;
		if(pRecordSet != NULL && !pRecordSet->adoEOF)
		{
			FieldPtr pFld =  pRecordSet->Fields->GetItem(_variant_t("MemberName")); // ID, NAME 저장
			_variant_t fldVal = pFld->GetValue();
			CString name = (LPCSTR)(_bstr_t)fldVal.bstrVal;

			strcpy_s(m_profileInfo.name, name);
			strcpy_s(m_profileInfo.id, loginInfo.id);
			
			result = 1;
			Send(&result, sizeof(int)); // 성공 전송
			Send((char*)&m_profileInfo, sizeof(m_profileInfo)); // 프로필 정보 전송
		}
		else
		{
			result = 0; // 실패 전송
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
