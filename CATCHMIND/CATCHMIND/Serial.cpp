// Serial.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Serial.h"
#include "CATCHMIND.h"
#include "CATCHMINDDlg.h"
#include "Data.h"
// CSerial

IMPLEMENT_DYNAMIC(CSerial, CCmdTarget)

CSerial::CSerial()
{

}

CSerial::~CSerial()
{
}

BEGIN_MESSAGE_MAP(CSerial, CCmdTarget)
END_MESSAGE_MAP()

// ����Ʈ ����
void CSerial::SetComPort(CString port, DWORD baudRate, BYTE dataBit, BYTE stopBit, BYTE parity )
{
	m_port = port;
	m_baudRate = baudRate;
	m_dataBit = dataBit;
	m_stopBit = stopBit;
	m_parity = parity;
}

// ����Ʈ ���� ����
BOOL CSerial::CreateComInfo()
{
	// offset: ���� ���ο��� ������ ���� ��ġ
	// offsethight: ���� ��ġ�� ���� �ܾ�(��ġ ������ ��� ��� �׿ܿ��� 0)
	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;

	// �̺�Ʈ ����
	m_osRead.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL ) ; 
	if (m_osRead.hEvent == NULL) 
	{
		return FALSE ; 
	}
	m_osWrite.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL ) ; 
	if (NULL == m_osWrite.hEvent) 
	{ 
		CloseHandle(m_osRead.hEvent) ; 
		return FALSE; 
	}

	return TRUE;
}

// ����Ʈ ���� ����õ�
BOOL CSerial::OpenComPort()
{
	// ��ü�� ���� �б�/���� ������ �����Ѵ�.
	m_comHandle = CreateFile(m_port, 
		GENERIC_READ | GENERIC_WRITE, // ���ٸ�� (�б�/���� ����)
		0, // �ٸ� ���α׷��� ���� ����
		NULL, // ���ȿ� ���� �Ӽ�
		OPEN_EXISTING, // ��� �����ΰ�
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, // ���� �Ӽ�
		NULL); // ���ø� ���� �ڵ鷯

	//����Ʈ���� �����͸� ��ȯ�ϴ� ����� char ������ �⺻���� ���� 
	//����. 
	SetCommMask( m_comHandle, EV_RXCHAR );
	// COM ��Ʈ ���� ũ�� ���� (��ġ ���� �Է�/��� ���� byte����)
	SetupComm(m_comHandle, 4096, 4096);
	//������ ��� �ڿ��� ����� ������ ��� �����͸� ����
	// ����ڿ��� �ڵ�,
	// ��� ���ذ�� Overlapped ���� �۾��� �����ϰ� ���� �۾��� �Ϸᰡ ���� �ʴ��� ��� ��ȯ
	// ��� ���ذ�� Overlapped �б� �۾��� �����ϰ� ���� �۾��� �Ϸᰡ ���� �ʴ��� ��� ��ȯ
	// ��� ���� Ŭ����
	// �Է� ���� Ŭ���� 
	PurgeComm( m_comHandle, PURGE_TXABORT | PURGE_RXABORT | 
		PURGE_TXCLEAR | PURGE_RXCLEAR );

	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 1000;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 1000;
	SetCommTimeouts(m_comHandle, &CommTimeOuts );

	BOOL connectionState;
	DCB dcb;
	GetCommState(m_comHandle, &dcb);
	dcb.BaudRate = m_baudRate;
	dcb.ByteSize = m_dataBit;
	dcb.StopBits = m_stopBit;
	dcb.Parity = m_parity;
	connectionState = SetCommState(m_comHandle, &dcb);

	if(connectionState)
	{
		AfxBeginThread((AFX_THREADPROC)ComThread,(LPVOID)this); 
		m_connected = TRUE;
	}
	else
	{
		m_connected = FALSE;
		CloseHandle(m_comHandle);
	}
	return connectionState;
}

// ����Ʈ ����
BOOL CSerial::DestoryCom()
{
	if(m_connected)
	{
		SetCommMask(m_comHandle, 0);
		EscapeCommFunction(m_comHandle, CLRDTR);
		PurgeComm(m_comHandle, PURGE_TXABORT | PURGE_RXABORT |
			PURGE_TXCLEAR | PURGE_RXCLEAR);
		CloseHandle(m_comHandle);
		m_connected = FALSE;
	}
	CloseHandle(m_osRead.hEvent);
	CloseHandle(m_osWrite.hEvent);
	return TRUE;
}


DWORD ComThread(LPVOID lpData)
{
	DWORD dwEvtMask; 
	OVERLAPPED os; 
	CSerial* pSerial = (CSerial*)lpData; 

	//�ڵ鿡 �ƹ��� ����Ʈ�� �� �پ� ������ ���� ���� 
	if (pSerial == NULL || !pSerial->IsKindOf( RUNTIME_CLASS(CSerial))) 
		return (DWORD)-1; 
	memset( &os, 0, sizeof(OVERLAPPED)); 
	os.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL);
	if (os.hEvent == NULL) 
	{ 
		AfxMessageBox("Failed to create event for thread! comm Error!"); 
		return FALSE; 
	} 
	if (!SetCommMask(pSerial->m_comHandle, EV_RXCHAR)) 
		return FALSE;
	while (pSerial->m_connected) 
	{ 
		dwEvtMask = 0; 
		WaitCommEvent(pSerial->m_comHandle, &dwEvtMask, NULL); 
		if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR) 
		{ 
			Header header;
			if(pSerial->ReadCom((char*)&header, sizeof(Header))) 
			{
				if(header.startBit != 0x21)
					continue;
				switch (header.command)
				{
				case MESSAGE : 
					{
						ChatMessage chatMessage;
						pSerial->ReadCom((char*)&chatMessage, header.dataSize);
						CString name = (LPSTR)chatMessage.name;
						CString message = (LPSTR)chatMessage.message;
						((CCATCHMINDDlg*)(AfxGetApp()->GetMainWnd()))->m_gameRoomDlg->AddMessageToList(name, message);
						break;				
					}
				case POINT :
					{
						Point point;
						pSerial->ReadCom((char*)&point, header.dataSize);
						((CCATCHMINDDlg*)(AfxGetApp()->GetMainWnd()))->m_gameRoomDlg->Draw(&point);
						break;
					}
				case JOINED_NEW_USER_PROFILE :
					{
						// RECV PROFILE BODY
						Profile profile;
						pSerial->ReadCom((char*)&profile, header.dataSize);
						pSerial->m_vProfile.push_back(profile);

						byte* imageData = new byte[4096];
						DWORD dwRead;
						ULONGLONG receiveSize = 0;

						CString imageName = profile.imageName;
						CString imagePath = "profileImage\\client\\" + imageName;
						CFile file;
						file.Open(imagePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
						while(dwRead = pSerial->ReadCom((LPSTR)imageData, 4096))
						{
							file.Write(imageData, dwRead);
						}

						delete imageData;
						file.Close();
						((CCATCHMINDDlg*)(AfxGetApp()->GetMainWnd()))->m_gameRoomDlg->AddProfileToList(&profile);

						//g_serial.WriteProfile(PROFILE_RECV_FROM_CLIENT);
						break;
					}
				case PROFILE_RECV_FROM_CLIENT :
					{
						// RECV PROFILE BODY
						Profile profile;
						pSerial->ReadCom((char*)&profile, header.dataSize);
						pSerial->m_vProfile.push_back(profile);

						byte* imageData = new byte[4096];
						DWORD dwRead;

						CString imageName = profile.imageName;
						CString imagePath = "profileImage\\client\\" + imageName;
						CFile file;
						file.Open(imagePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
						while(dwRead = pSerial->ReadCom((LPSTR)imageData, 4096))
						{
							file.Write(imageData, dwRead);
						}

						delete imageData;
						file.Close();
						((CCATCHMINDDlg*)(AfxGetApp()->GetMainWnd()))->m_gameRoomDlg->AddProfileToList(&profile);
						break;
					}
				case CHANGE_MODE :
					{
						// RECV BODY
						int mode;
						pSerial->ReadCom((LPSTR)&mode, header.dataSize);
						// LOGIC
						((CCATCHMINDDlg*)(AfxGetApp()->GetMainWnd()))->m_gameRoomDlg->SetMode(mode);
						break;
					}
				case QUIZ :
					{
						// RECV BODY
						char* pChar = new char[header.dataSize];
						pSerial->ReadCom(pChar, header.dataSize);
						CString quiz = (LPSTR)pChar;
						delete[] pChar;

						// LOGIC
						((CCATCHMINDDlg*)(AfxGetApp()->GetMainWnd()))->m_gameRoomDlg->SetQuiz(quiz);

						break;
					}
				}
			}
		} 
	} 
	CloseHandle( os.hEvent ) ; 
	return TRUE;
}


// ����Ʈ�κ��� ������ ����
int CSerial::ReadCom(LPSTR lpszData, int maxLength)
{
	BOOL readState;
	COMSTAT comStat;
	DWORD dwError;
	DWORD dwLength;

	ClearCommError(m_comHandle, &dwError, &comStat);
	dwLength = min((DWORD)maxLength, comStat.cbInQue);
	if(dwLength > 0)
	{
		readState = ReadFile(m_comHandle, lpszData, dwLength, &dwLength, &m_osRead);
		if(!readState)
		{
			AfxMessageBox("Read Error");
		}
	}
	return dwLength;
}

// Data Write
BOOL CSerial::WriteCom(LPSTR lpByte, DWORD dwBytesToWrite)
{
	BOOL writeState;
	DWORD dwBytesWritten;
	writeState = WriteFile(m_comHandle, lpByte, dwBytesToWrite, &dwBytesWritten, &m_osWrite);
	if(writeState)
	{
		AfxMessageBox("Write Error");
	}
	return TRUE;
}

// Write Header
void CSerial::WriteHeader(byte command, int dataSize)
{
	Header header;
	header.startBit = 0x21;
	header.command = command;
	header.dataSize = dataSize;
	WriteCom((char*)&header, sizeof(Header));
}

// Write Chatting Message
void CSerial::WriteChatMessage(CString name, CString message)
{
	ChatMessage chatMessage;
	strcpy_s(chatMessage.name, name);
	strcpy_s(chatMessage.message, message);
	
	WriteHeader(MESSAGE, sizeof(ChatMessage));
	WriteCom((char*)&chatMessage, sizeof(ChatMessage));
}

// Write Quiz
void CSerial::WriteQuiz(CString quiz)
{
	int quizSize= quiz.GetLength() + 1;
	char *pQuiz = new char[quizSize];
	memcpy(pQuiz, quiz.GetBuffer(), quizSize);

	// SEND HEADER
	WriteHeader(QUIZ, quizSize);

	// SEND BODY
	WriteCom(pQuiz, quizSize);

	delete[] pQuiz;
}


// Write Point (Draw)
void CSerial::WritePoint(CPoint startPoint, CPoint endPoint, int thinkness, COLORREF rgb)
{
	Point point;
	point.startX = (short)startPoint.x;
	point.startY = (short)startPoint.y;
	point.endX = (short)endPoint.x;
	point.endY = (short)endPoint.y;
	point.thinkness = thinkness;
	point.rgb = rgb;

	WriteHeader(POINT, sizeof(Point));
	WriteCom((char*)&point, sizeof(Point));
}

// Write Game Mode
void CSerial::WriteMode(int mode)
{
	// SEND HEADER
	WriteHeader(CHANGE_MODE, sizeof(int));
	// SEND BODY
	WriteCom((LPSTR)&mode, sizeof(int));
}

// Write Profile (Draw)
void CSerial::WriteProfile(byte command)
{
	// SEND HEADER
	WriteHeader(command, sizeof(Profile));

	// SEND PROFILE BODY
	Profile profile;
	strcpy_s(profile.name, g_member.name);
	strcpy_s(profile.id, g_member.id);
	strcpy_s(profile.imageName, g_member.imageName);
	WriteCom((char*)&profile, sizeof(Profile));

	// SEND IMAGE BODY
	CFile imageFile;
	byte* imageData = new byte[4096];
	DWORD dwRead;

	CString imageName;
	imageName.Format("profileImage\\%s", g_member.imageName);
	imageFile.Open(imageName, CFile::modeReadWrite | CFile::typeBinary);

	while(dwRead = imageFile.Read(imageData, 4096))
	{
		WriteCom((LPSTR)imageData, dwRead);
	}
	delete imageData;
	imageFile.Close();
}

void CSerial::SetHwnd(HWND hwnd)
{
	m_hWnd = hwnd;
}

